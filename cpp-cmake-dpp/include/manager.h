#pragma once
#include <dpp/dpp.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "ICommand.h"
#include "IUIBuilder.h"
#include "file_manager.h"
#include "cmd_sys.h"
#include "cmd_config.h"

class Manager {
public:
    Manager(dpp::cluster& bot);

    void register_commands(dpp::cluster& bot);
    void handle_slashcommand(const dpp::slashcommand_t& slash);
    void handle_button_click(const dpp::button_click_t& click);
    void handle_select(const dpp::select_click_t &select);
    void handle_form_submit(const dpp::form_submit_t& submit);

private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> command_map;
    std::vector<std::pair<std::string, std::string>> command_metadata;

    // Instantiate command handlers
    dpp::cluster& bot;
    System system_cmd;
};
