#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#include <string>
#include <map>

std::string trim(std::string line);
std::map<std::string, std::string> load_config(const std::string& path);

#endif