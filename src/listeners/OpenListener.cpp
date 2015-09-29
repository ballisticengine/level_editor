#include "listeners/OpenListener.hpp"

OpenListener::OpenListener() {
    ui->addDocument("open_dialog.rml", "open-dialog");
}

OpenListener::~OpenListener() {
}

void OpenListener::ProcessEvent(Rocket::Core::Event& event) {

}