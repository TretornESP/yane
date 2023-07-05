#include "controller.h"

void controller_init(struct controller *controller) {
    controller->up = 0;
    controller->down = 0;
    controller->left = 0;
    controller->right = 0;
    controller->a = 0;
    controller->b = 0;
    controller->select = 0;
    controller->start = 0;
}

void controller_up(struct controller *controller) {
    controller->up = 1;
}
void controller_down(struct controller *controller) {
    controller->down = 1;
}
void controller_left(struct controller *controller) {
    controller->left = 1;
}
void controller_right(struct controller *controller) {
    controller->right = 1;
}
void controller_a(struct controller *controller) {
    controller->a = 1;
}
void controller_b(struct controller *controller) {
    controller->b = 1;
}
void controller_select(struct controller *controller) {
    controller->select = 1;
}
void controller_start(struct controller *controller) {
    controller->start = 1;
}

void controller_up_release(struct controller *controller) {
    controller->up = 0;
}
void controller_down_release(struct controller *controller) {
    controller->down = 0;
}
void controller_left_release(struct controller *controller) {
    controller->left = 0;
}
void controller_right_release(struct controller *controller) {
    controller->right = 0;
}
void controller_a_release(struct controller *controller) {
    controller->a = 0;
}
void controller_b_release(struct controller *controller) {
    controller->b = 0;
}
void controller_select_release(struct controller *controller) {
    controller->select = 0;
}
void controller_start_release(struct controller *controller) {
    controller->start = 0;
}