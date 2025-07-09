#pragma once
#include <dpp/dpp.h>
#include <functional>
#include <string>

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
    
    virtual bool has_options() const { return false; }
    virtual std::vector<dpp::command_option> get_options() const { return {}; }
    
    virtual void on_slash(const dpp::slashcommand_t& slash, const dpp::cluster& bot = dpp::cluster()) {};
    virtual void on_click(const dpp::button_click_t& click, const dpp::cluster& bot = dpp::cluster()) {};
    virtual void on_select(const dpp::select_click_t& select, const dpp::cluster& bot = dpp::cluster()) {};
    virtual void on_form_submit(const dpp::form_submit_t& submit, const dpp::cluster& bot = dpp::cluster()) {};
};

class LambdaCommand : public ICommand {
public:
    LambdaCommand(std::string cmd_name, std::string cmd_desc, std::function<void(const dpp::slashcommand_t&)> fn_slash)
        : _name(std::move(cmd_name)), _desc(std::move(cmd_desc)), slash_handler(std::move(fn_slash)) {}

    LambdaCommand(std::string cmd_name, std::string cmd_desc, std::function<void(const dpp::button_click_t&)> fn_click)
        : _name(std::move(cmd_name)), _desc(std::move(cmd_desc)), click_handler(std::move(fn_click)) {}

    LambdaCommand(std::string cmd_name, std::string cmd_desc, std::function<void(const dpp::select_click_t&)> fn_select)
        : _name(std::move(cmd_name)), _desc(std::move(cmd_desc)), select_handler(std::move(fn_select)) {}

    std::string name() const override { return _name; }
    std::string description() const override { return _desc; }

    void on_slash(const dpp::slashcommand_t& slash, const dpp::cluster& bot = dpp::cluster()) override { slash_handler(slash); }
    void on_click(const dpp::button_click_t& click, const dpp::cluster& bot = dpp::cluster()) override { click_handler(click); }
    void on_select(const dpp::select_click_t& select, const dpp::cluster& bot = dpp::cluster()) override { select_handler(select); }

private:
    std::string _name;
    std::string _desc;
    std::function<void(const dpp::slashcommand_t&)> slash_handler;
    std::function<void(const dpp::button_click_t&)> click_handler;
    std::function<void(const dpp::select_click_t&)> select_handler;
};
