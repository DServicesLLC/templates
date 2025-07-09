#include "manager.h"

#include <print>
#include <memory>

Manager::Manager(dpp::cluster& bot) : bot(bot) {
    std::vector<std::unique_ptr<ICommand>> cmds;

    cmds.emplace_back(std::make_unique<LambdaCommand>(
        "ping", "Ping the bot",
        [&](const dpp::slashcommand_t& e) { system_cmd.ping(e); }
    ));

    cmds.emplace_back(std::make_unique<ConfigCommand>());

    for (auto& cmd : cmds) {
        command_metadata.emplace_back(cmd->name(), cmd->description());
        command_map[cmd->name()] = std::move(cmd);
    }
}

void Manager::register_commands(dpp::cluster& bot) {
    std::println("[INFO] Registering slash commands...");

    for (const auto& [name, description] : command_metadata) {
        auto it = command_map.find(name);
        if (it != command_map.end() && it->second->has_options()) {
            // Create command with options
            dpp::slashcommand cmd(name, description, bot.me.id);
            auto options = it->second->get_options();
            
            for (const auto& option : options) {
                cmd.add_option(option);
            }
            bot.global_command_create(cmd);
            std::println("[INFO] /{} command with {} options added successfully.", name, options.size());
        } else {
            // Regular command without options
            bot.global_command_create(
                dpp::slashcommand(name, description, bot.me.id)
            );
            std::println("[INFO] /{} command added successfully.", name);
        }
    }
}

void Manager::handle_slashcommand(const dpp::slashcommand_t& slash) {
    auto it = command_map.find(slash.command.get_command_name());
    if (it != command_map.end()) {
        it->second->on_slash(slash, bot);
    } else {
        std::println("[WARN] Unknown slash command: {}", slash.command.get_command_name());
    }
}

void Manager::handle_button_click(const dpp::button_click_t& click) {
    if (click.custom_id == "config_modal") {
        ConfigCommand config_cmd;
        dpp::interaction_modal_response modal = config_cmd.build_modal();
        click.reply(modal);
    } else {
        std::println("[INFO] Button clicked by user {}: {}", click.command.usr.id, click.custom_id);
    }
}

void Manager::handle_select(const dpp::select_click_t& select) {
    // Handle select menu interactions here
    std::println("[INFO] Select menu used by user {}", select.command.usr.id);
}

void Manager::handle_form_submit(const dpp::form_submit_t& submit) {
    if (submit.custom_id == "config_modal") {
        std::string guild_id = std::to_string(submit.command.guild_id);
        std::string new_prefix = std::get<std::string>(submit.components[0].components[0].value);
        
        FileManager::save(guild_id, "prefix", new_prefix);
        
        submit.reply(dpp::message(std::format("Prefix updated to: `{}`", new_prefix)));
        std::println("[INFO] Prefix updated for guild {} to: {}", guild_id, new_prefix);
    } else {
        std::println("[INFO] Form submitted by user {}: {}", submit.command.usr.id, submit.custom_id);
    }
}
