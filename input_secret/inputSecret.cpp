#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Button.H>
#include <FL/fl_utf8.h>
#include <FL/fl_ask.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Box.H>
#include "inputSecret.h"

constexpr size_t MAX_UNICODE_SYMBOLS = 10000;

void download_callback(Fl_Widget*, void* data) {
    Fl_Text_Buffer* buff = (Fl_Text_Buffer*)data;
    
    std::string secret_text = buff->text();
    std::u8string_view u8sv = std::u8string_view(reinterpret_cast<const char8_t*>(secret_text.data()), secret_text.size());
    
    size_t unicode_symbols_count = utf8_unicode_count(u8sv);
    if (unicode_symbols_count > MAX_UNICODE_SYMBOLS) {
        fl_alert("Text is too long!\nEntered: %zu symbols\nMaximum allowed: %zu symbols", unicode_symbols_count, MAX_UNICODE_SYMBOLS);
        return;
    }

    fs::path display_secret_exe_path = fs::path(".\\..\\..\\display_secret\\build\\displaySecret.exe");
    try {
        fs::path downloaded_file = copy_file_to_downloads(display_secret_exe_path);

        embed_secret(downloaded_file, secret_text);

        self_sign_executable(downloaded_file);

        fl_alert("Successfully downloaded file with embedded secret to \n%s", downloaded_file.string().c_str());
    } catch (std::runtime_error e){
        fl_alert("Error: %s", e.what());
    }
}

int main() {
    Fl::scheme("gtk+");
    Fl_Window* window = new Fl_Window(800, 600, "Text Embedder App");
    window->color(fl_rgb_color(29, 70, 110));
    Fl_Box* label = new Fl_Box(50, 20, 700, 30, "Enter secret text (max 10 000 symbols):");
    label->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    label->labelfont(FL_HELVETICA_BOLD);
    label->labelsize(26);
    label->labelcolor(fl_rgb_color(255, 255, 255));

    Fl_Text_Buffer* buff = new Fl_Text_Buffer();
    Fl_Text_Editor* editor = new Fl_Text_Editor(50, 60, 700, 480);
    editor->buffer(buff);
    editor->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
    editor->textfont(FL_HELVETICA);
    editor->textsize(16);

    Fl_Button* btn = new Fl_Button(350, 550, 100, 40, "Download");
    btn->callback(download_callback, buff);
    btn->labelfont(FL_HELVETICA_BOLD);
    btn->labelsize(16);
    btn->color(fl_rgb_color(53, 126, 198));
    btn->labelcolor(fl_rgb_color(255, 255, 255));

    window->resizable(editor);
    window->size_range(600, 400);
    window->end();
    window->show();

    return Fl::run();
}
