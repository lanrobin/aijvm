#pragma once

#include "classfile/class_file.h"
#include "classfile/jmod_reader.h"

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace aijvm::classloader {

/// §5.3 Creation and Loading
/// A ClassLoader resolves a canonical class name (e.g. "java/util/ArrayList")
/// to a parsed ClassFile instance.
///
/// Two loaders are supported:
///   - System (bootstrap): reads from java.base.jmod via the --bj path.
///   - Customer (application): reads .class files from the --cp directory.
///
/// Delegation: system loader is tried first; on miss, customer loader is tried.
/// Successfully loaded classes are cached to avoid redundant parsing.
class ClassLoader {
public:
    /// Construct the class loader with the boot jmod directory and class path.
    /// @param boot_jmod_dir  Directory containing java.base.jmod (--bj).
    /// @param class_path     Directory containing user .class files (--cp).
    ClassLoader(const std::filesystem::path& boot_jmod_dir,
                const std::filesystem::path& class_path);

    ~ClassLoader();
    ClassLoader(ClassLoader&&) noexcept;
    ClassLoader& operator=(ClassLoader&&) noexcept;
    ClassLoader(const ClassLoader&) = delete;
    ClassLoader& operator=(const ClassLoader&) = delete;

    /// Load a class by its canonical name (e.g. "java/util/ArrayList").
    /// §5.3: First delegates to the system (bootstrap) loader, then to the
    /// customer (application) loader.
    /// Returns a shared pointer to the cached ClassFile, or nullptr if not found.
    [[nodiscard]] std::shared_ptr<classfile::ClassFile>
    load_class(std::string_view class_name);

    /// Check whether a class has already been loaded (cached).
    [[nodiscard]] bool is_loaded(std::string_view class_name) const;

    /// Get all loaded (cached) ClassFile instances.
    /// Safe to call during STW pause when all mutator threads are parked.
    /// Not thread-safe for concurrent access — use only under STW or
    /// single-threaded initialization contexts.
    [[nodiscard]] std::vector<std::shared_ptr<classfile::ClassFile>>
    get_all_loaded_classes() const;

private:
    /// Try to load from java.base.jmod (system/bootstrap loader).
    std::shared_ptr<classfile::ClassFile>
    load_from_system(std::string_view class_name);

    /// Try to load from the --cp directory (customer/application loader).
    std::shared_ptr<classfile::ClassFile>
    load_from_customer(std::string_view class_name);

    std::filesystem::path class_path_;
    std::optional<classfile::JmodReader> jmod_reader_;
    std::unordered_map<std::string, std::shared_ptr<classfile::ClassFile>> cache_;
};

} // namespace aijvm::classloader
