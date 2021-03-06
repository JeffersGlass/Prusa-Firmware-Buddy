//window_dlg_strong_warning.cpp

#include "window_dlg_strong_warning.hpp"
#include "display_helper.h"
#include "i18n.h"
#include "ScreenHandler.hpp"

window_dlg_strong_warning_t::window_dlg_strong_warning_t()
    : AddSuperWindow<IDialog>(GuiDefaults::RectScreenBodyNoFoot, IDialog::IsStrong::yes)
    , text(this, GuiDefaults::RectScreenBodyNoFoot, is_multiline::yes, is_closed_on_click_t::no) {
}

void window_dlg_strong_warning_t::Show(string_view_utf8 txt) {
    static window_dlg_strong_warning_t dlg;
    if (!dlg.GetParent()) {
        window_t *parent = Screens::Access()->Get();
        if (parent) {
            parent->RegisterSubWin(&dlg);
            dlg.text.SetText(txt);

            if (window_t::GetCapturedWindow() != &dlg) {
                dlg.StoreCapture();
                dlg.SetCapture();
            }
        }
    }
}

void window_dlg_strong_warning_t::windowEvent(EventLock /*has private ctor*/, window_t *sender, GUI_event_t event, void *param) {
    if (event == GUI_event_t::CLICK) { //todo use timer
        if (GetParent()) {
            GetParent()->UnregisterSubWin(this);
            releaseCapture();
        }
    } else
        SuperWindowEvent(sender, event, param);
}
