#include "button.hpp"

bool button(Game *context, std::string label, Vector2 position, Vector2 size) {
    bool clicked = false;
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.height = size.y;
    rect.width = size.x;
    // Draw Border
    DrawRectangleLinesEx(rect, 2, BLACK);

    // Draw background on hover
    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
        DrawRectangleRec(rect, {0, 0, 0, 10});
        context->ui.mouseOnClickable = true;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicked = true;
        }
    }

    // Draw lable
    Vector2 labelSize = MeasureTextEx(context->asset.font, label.c_str(), 20, 0);
    Vector2 center;
    center.x = rect.x + (rect.width/2.0) - (labelSize.x/2.0);
    center.y = rect.y + (rect.height/2.0) - (labelSize.y/2.0);
    DrawTextEx(context->asset.font, label.c_str(), center, 20, 0, BLACK);

    return clicked;
}
