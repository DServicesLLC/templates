#pragma once
#include <dpp/dpp.h>
#include <string>

class IUIBuilder {
public:
    virtual ~IUIBuilder() = default;
    virtual dpp::message build_main_message() const { return dpp::message(); };
    virtual dpp::message build_response_message() const { return dpp::message(); };
    virtual dpp::interaction_modal_response build_modal() const { return dpp::interaction_modal_response(); };

protected:
    dpp::message message;
    dpp::message response_message;
    dpp::interaction_modal_response modal;
};
