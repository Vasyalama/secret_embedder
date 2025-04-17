#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/fl_draw.H>
#include <string>
#include <FL/Fl_Scheme.H>

const size_t MAX_UTF8_CODE_LEN = 4;

char text[MAX_UTF8_CODE_LEN * 10000 + 4] = "            ";

void copy_callback(Fl_Widget* widget, void* data) {
    Fl_Text_Buffer* buff = (Fl_Text_Buffer*)data;
    Fl::copy(text, buff->length(), 2);
}

int main() {
    Fl::scheme("gtk+");
    Fl_Window* window = new Fl_Window(800, 600, "Display Secret App");
    window->color(fl_rgb_color(29, 70, 110));

    Fl_Box* label = new Fl_Box(50, 20, 700, 30, "Secret text:");
    label->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    label->labelfont(FL_HELVETICA_BOLD);
    label->labelsize(26);
    label->labelcolor(fl_rgb_color(255, 255, 255));

    Fl_Text_Buffer* buff = new Fl_Text_Buffer();
    Fl_Text_Display* text_disp = new Fl_Text_Display(50, 60, 700, 480);
    buff->text(text);
    text_disp->buffer(buff);
    text_disp->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0); 
    text_disp->textfont(FL_HELVETICA);
    text_disp->textsize(16); 

    Fl_Button* copy_button = new Fl_Button(350, 550, 100, 40, "Copy Text");
    copy_button->callback(copy_callback, buff);
    copy_button->labelfont(FL_HELVETICA_BOLD);
    copy_button->labelsize(16);
    copy_button->color(fl_rgb_color(53, 126, 198));
    copy_button->labelcolor(fl_rgb_color(255, 255, 255));

    window->end();
    window->resizable(text_disp); 
    window->show();

    return Fl::run();
}

