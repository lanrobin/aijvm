#include "classloader/class_loader.h"
#include "utils/logger.h"

#include <fstream>
#include <format>

namespace aijvm::classloader {

ClassLoader::ClassLoader(const std::filesystem::path& boot_jmod_dir,
                         const std::filesystem::path& class_path)
    : class_path_(class_path)
{
    // §5.3.1 Bootstrap class loader: open java.base.jmod and keep the handle
    auto jmod_path = boot_jmod_dir / "java.base.jmod";
    auto reader = classfile::JmodReader::open(jmod_path);
    if (reader) {
        jmod_reader_ = std::move(*reader);
        AIJVM_LOG_INFO("System class loader: opened {}", jmod_path.string());
    } else {
        AIJVM_LOG_WARN("System class loader: failed to open {}", jmod_path.string());
    }

    AIJVM_LOG_INFO("Customer class loader: class path = {}", class_path_.string());
}

ClassLoader::~ClassLoader() = default;
ClassLoader::ClassLoader(ClassLoader&&) noexcept = default;
ClassLoader& ClassLoader::operator=(ClassLoader&&) noexcept = default;

std::shared_ptr<classfile::ClassFile>
ClassLoader::load_class(std::string_view class_name) {
    // Check cache first
    auto key = std::string(class_name);
    if (auto it = cache_.find(key); it != cache_.end()) {
        AIJVM_LOG_DEBUG("Class '{}' found in cache", class_name);
        return it->second;
    }

    // §5.3: Delegation - try system loader first, then customer loader
    if (auto cf = load_from_system(class_name)) {
        cache_.emplace(key, cf);
        return cf;
    }

    if (auto cf = load_from_customer(class_name)) {
        cache_.emplace(key, cf);
        return cf;
    }

    AIJVM_LOG_WARN("Class '{}' not found by any class loader", class_name);
    return nullptr;
}

bool ClassLoader::is_loaded(std::string_view class_name) const {
    return cache_.contains(std::string(class_name));
}

std::shared_ptr<classfile::ClassFile>
ClassLoader::load_from_system(std::string_view class_name) {
    if (!jmod_reader_) {
        return nullptr;
    }

    // JMOD stores classes under "classes/" prefix, e.g. "classes/java/util/ArrayList.class"
    auto entry_path = std::format("classes/{}.class", class_name);
    auto data = jmod_reader_->read_file(entry_path);
    if (!data) {
        return nullptr;
    }

    try {
        auto cf = std::make_shared<classfile::ClassFile>(std::move(*data));
        AIJVM_LOG_DEBUG("System class loader: loaded '{}'", class_name);
        return cf;
    } catch (const classfile::ClassFileParseError& e) {
        AIJVM_LOG_ERROR("System class loader: failed to parse '{}': {}",
                        class_name, e.what());
        return nullptr;
    }
}

std::shared_ptr<classfile::ClassFile>
ClassLoader::load_from_customer(std::string_view class_name) {
    // Convert canonical name "java/util/ArrayList" to filesystem path
    // "java/util/ArrayList.class" relative to class_path_
    auto relative = std::filesystem::path(std::string(class_name) + ".class");
    auto full_path = class_path_ / relative;

    std::error_code ec;
    if (!std::filesystem::is_regular_file(full_path, ec) || ec) {
        return nullptr;
    }

    std::ifstream ifs(full_path, std::ios::binary | std::ios::ate);
    if (!ifs) {
        return nullptr;
    }

    auto size = ifs.tellg();
    if (size < 0) {
        return nullptr;
    }
    ifs.seekg(0, std::ios::beg);

    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));
    if (size > 0 && !ifs.read(reinterpret_cast<char*>(data.data()), size)) {
        AIJVM_LOG_WARN("Customer class loader: failed to read '{}'", full_path.string());
        return nullptr;
    }

    try {
        auto cf = std::make_shared<classfile::ClassFile>(std::move(data));
        AIJVM_LOG_DEBUG("Customer class loader: loaded '{}' from {}",
                        class_name, full_path.string());
        return cf;
    } catch (const classfile::ClassFileParseError& e) {
        AIJVM_LOG_ERROR("Customer class loader: failed to parse '{}': {}",
                        class_name, e.what());
        return nullptr;
    }
}

} // namespace aijvm::classloader
