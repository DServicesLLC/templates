#pragma once
#include <dpp/dpp.h>
#include "ICommand.h"
#include "IUIBuilder.h"

class ConfigCommand : public ICommand, public IUIBuilder {
public:
    std::string name() const override { return "config"; }
    std::string description() const override { return "Configure bot settings"; }
    
    bool has_options() const override { return true; }
    std::vector<dpp::command_option> get_options() const override;
    
    void on_slash(const dpp::slashcommand_t& slash, const dpp::cluster& bot = dpp::cluster()) override;
    
    dpp::message build_main_message() const override;
    dpp::interaction_modal_response build_modal() const override;
};
