I want to adopt c++ logging framework spdlog  to my project, please replace all the console printing code to spdlog code. Here are the logging config:
1. Store the logs to a file logs/log_{level}.log, where level is the log level such as Error, Warning, Info, Debug, Verbose etc.
2. Each log will appened logging time, thread, class, method info to it.
3. Make the log level globally controlled.
4. Rotate the log at each run or daily rotation or size rotation by 512M.
5. For the error and warning logs, put them into console as well with error color RED and warning YELLOW.
6. Update the CMakeList.txt as well also update UbuntuRequirements.txt if customer has to install extra packages.