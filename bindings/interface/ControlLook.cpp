#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ControlLook.h>
#include <InterfaceDefs.h>
#include <Alignment.h>
#include <Font.h>
#include <Rect.h>
#include <Slider.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace BPrivate;



class PyBControlLook : public BControlLook {
public:
    using BControlLook::BControlLook;

    BAlignment DefaultLabelAlignment() const override {
        PYBIND11_OVERRIDE_PURE(BAlignment, BControlLook, DefaultLabelAlignment, );
    }

    float DefaultLabelSpacing() const override {
        PYBIND11_OVERRIDE_PURE(float, BControlLook, DefaultLabelSpacing, );
    }

    float DefaultItemSpacing() const override {
        PYBIND11_OVERRIDE_PURE(float, BControlLook, DefaultItemSpacing, );
    }

    uint32 Flags(BControl* control) const override {
        PYBIND11_OVERRIDE_PURE(uint32, BControlLook, Flags, control);
    }

    void DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
                         const rgb_color& base, const rgb_color& background,
                         uint32 flags = 0, uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonFrame, view, rect, updateRect, base, background, flags, borders);
    }
    void DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
						float radius, const rgb_color& base, const rgb_color& background,
						uint32 flags = 0, uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonFrame, view, rect, updateRect, radius, base, background, flags, borders);
    }
    void DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
						float leftTopRadius, float rightTopRadius, float leftBottomRadius,
						float rightBottomRadius, const rgb_color& base, const rgb_color& background,
						uint32 flags = 0, uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonFrame, view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, background, flags, borders);
    }
    void DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
							const rgb_color& base, uint32 flags = 0, uint32 borders = B_ALL_BORDERS,
							orientation orientation = B_HORIZONTAL) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonBackground, view, rect, updateRect, base, flags, borders, orientation);
    }
    void DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
							float radius, const rgb_color& base, uint32 flags = 0,
							uint32 borders = B_ALL_BORDERS, orientation orientation = B_HORIZONTAL) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonBackground, view, rect, updateRect, radius, base, flags, borders, orientation);
    }
    void DrawButtonBackground(BView* view, BRect& rect,
									const BRect& updateRect,
									float leftTopRadius,
									float rightTopRadius,
									float leftBottomRadius,
									float rightBottomRadius,
									const rgb_color& base,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS,
									orientation orientation = B_HORIZONTAL) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonBackground, view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
    }
    void DrawMenuBarBackground(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuBarBackground, view, rect, updateRect, base, flags, borders);
    }
    void DrawMenuFieldFrame(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									const rgb_color& background,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldFrame, view, rect, updateRect, base, background, flags, borders);
    }
    void DrawMenuFieldFrame(BView* view, BRect& rect,
									const BRect& updateRect,
									float radius,
									const rgb_color& base,
									const rgb_color& background,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldFrame, view, rect, updateRect, radius, base, background, flags, borders);
    }
    void DrawMenuFieldFrame(BView* view, BRect& rect,
									const BRect& updateRect,
									float leftTopRadius,
									float rightTopRadius,
									float leftBottomRadius,
									float rightBottomRadius,
									const rgb_color& base,
									const rgb_color& background,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldFrame, view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, background, flags, borders);
    }
    void DrawMenuFieldBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									const rgb_color& base, bool popupIndicator,
									uint32 flags = 0) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldBackground, view, rect, updateRect, base, popupIndicator, flags);
    }
    void DrawMenuFieldBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									float radius, const rgb_color& base,
									bool popupIndicator, uint32 flags = 0) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldBackground, view, rect, updateRect, radius, base, popupIndicator, flags);
    }
    void DrawMenuFieldBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									float leftTopRadius,
									float rightTopRadius,
									float leftBottomRadius,
									float rightBottomRadius,
									const rgb_color& base,
									bool popupIndicator, uint32 flags = 0) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldBackground, view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, popupIndicator, flags);
    }
    void DrawMenuFieldBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									const rgb_color& base, uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuFieldBackground, view, rect, updateRect, base, flags, borders);
    }
    void DrawMenuBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									const rgb_color& base, uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuBackground, view, rect, updateRect, base, flags, borders);
    }
    void DrawMenuItemBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									const rgb_color& base, uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawMenuItemBackground, view, rect, updateRect, base, flags, borders);
    }
    void DrawStatusBar(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									const rgb_color& barColor,
									float progressPosition) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawStatusBar, view, rect, updateRect, base, barColor, progressPosition);
    }
    void DrawCheckBox(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									uint32 flags = 0) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawCheckBox, view, rect, updateRect, base, flags);
    }
    void DrawRadioButton(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									uint32 flags = 0) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawRadioButton, view, rect, updateRect, base, flags);
    }
    void DrawScrollBarBackground(BView* view,
									BRect& rect1, BRect& rect2,
									const BRect& updateRect,
									const rgb_color& base, uint32 flags,
									orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollBarBackground, view, rect1, rect2, updateRect, base, flags, orientation);
    }
    void DrawScrollBarBackground(BView* view,
									BRect& rect, const BRect& updateRect,
									const rgb_color& base, uint32 flags,
									orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollBarBackground, view, rect, updateRect, base, flags, orientation);
    }
    void DrawScrollViewFrame(BView* view,
									BRect& rect, const BRect& updateRect,
									BRect verticalScrollBarFrame,
									BRect horizontalScrollBarFrame,
									const rgb_color& base,
									border_style borderStyle,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollViewFrame, view, rect, updateRect,verticalScrollBarFrame,horizontalScrollBarFrame, base, borderStyle, flags, borders);
    }
    void DrawArrowShape(BView* view,
									BRect& rect, const BRect& updateRect,
									const rgb_color& base, uint32 direction,
									uint32 flags = 0,
									float tint = B_DARKEN_MAX_TINT) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawArrowShape, view, rect, updateRect, base, direction, flags, tint);
    }
    rgb_color SliderBarColor(const rgb_color& base) override {
        PYBIND11_OVERRIDE_PURE(rgb_color, BControlLook, SliderBarColor, base);
    }
    void DrawSliderBar(BView* view, BRect rect,
									const BRect& updateRect,
									const rgb_color& base,
									rgb_color leftFillColor,
									rgb_color rightFillColor,
									float sliderScale, uint32 flags,
									orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawSliderBar, view, rect, updateRect, base, leftFillColor, rightFillColor, sliderScale, flags, orientation);
    }
    void DrawSliderBar(BView* view, BRect rect,
									const BRect& updateRect,
									const rgb_color& base, rgb_color fillColor,
									uint32 flags, orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawSliderBar, view, rect, updateRect, base, fillColor, flags, orientation);
    }
    void DrawSliderThumb(BView* view, BRect& rect, const BRect& updateRect,
                         const rgb_color& base, uint32 flags,
                         orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            BControlLook,
            DrawSliderThumb,
            view, rect, updateRect, base, flags, orientation);
    }
    void DrawSliderTriangle(BView* view, BRect& rect, const BRect& updateRect,
                            const rgb_color& base, uint32 flags,
                            orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            BControlLook,
            DrawSliderTriangle,
            view, rect, updateRect, base, flags, orientation);
    }
    void DrawSliderTriangle(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									const rgb_color& fill, uint32 flags,
									orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            BControlLook,
            DrawSliderTriangle,
            view, rect, updateRect, base, fill, flags, orientation);
    }
    void DrawSliderHashMarks(BView* view, BRect& rect, const BRect& updateRect,
                             const rgb_color& base, int32 count,
                             hash_mark_location location, uint32 flags,
                             orientation orientation) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            BControlLook,
            DrawSliderHashMarks,
            view, rect, updateRect, base, count, location, flags,
            orientation);
    }
    void DrawActiveTab(BView* view, BRect& rect, const BRect& updateRect,
                   const rgb_color& base, uint32 flags = 0,
                   uint32 borders = B_ALL_BORDERS, uint32 side = B_TOP_BORDER,
                   int32 index = 0, int32 selected = -1,
                   int32 first = 0, int32 last = 0) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            BControlLook,
            DrawActiveTab,
            view, rect, updateRect, base, flags, borders, side, index, selected,
            first, last);
     }
     void DrawInactiveTab(BView* view, BRect& rect, const BRect& updateRect,
                     const rgb_color& base, uint32 flags,
                     uint32 borders = B_ALL_BORDERS, uint32 side = B_TOP_BORDER,
                     int32 index = 0, int32 selected = -1,
                     int32 first = 0, int32 last = 0) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawInactiveTab, view, rect, updateRect, base,
        flags, borders, side, index, selected, first, last);
}
void DrawSplitter(BView* view, BRect& rect, const BRect& updateRect,
                  const rgb_color& base, orientation orientation,
                  uint32 flags = 0, uint32 borders = B_ALL_BORDERS) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawSplitter, view, rect, updateRect, base,
        orientation, flags, borders);
}
void DrawBorder(BView* view, BRect& rect, const BRect& updateRect,
                const rgb_color& base, border_style borderStyle,
                uint32 flags = 0, uint32 borders = B_ALL_BORDERS) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawBorder, view, rect, updateRect, base,
        borderStyle, flags, borders);
}
void DrawRaisedBorder(BView* view, BRect& rect, const BRect& updateRect,
                      const rgb_color& base, uint32 flags = 0,
                      uint32 borders = B_ALL_BORDERS) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawRaisedBorder, view, rect, updateRect, base,
        flags, borders);
}
void DrawGroupFrame(BView* view, BRect& rect, const BRect& updateRect,
                    const rgb_color& base, uint32 borders = B_ALL_BORDERS) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawGroupFrame, view, rect, updateRect, base,
        borders);
}
void DrawTextControlBorder(BView* view, BRect& rect, const BRect& updateRect,
                           const rgb_color& base, uint32 flags = 0,
                           uint32 borders = B_ALL_BORDERS) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawTextControlBorder, view, rect, updateRect,
        base, flags, borders);
}
void DrawLabel(BView* view, const char* label, BRect rect,
               const BRect& updateRect, const rgb_color& base, uint32 flags,
               const rgb_color* textColor = nullptr) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawLabel, view, label, rect, updateRect, base,
        flags, textColor);
}
void DrawLabel(BView* view, const char* label, BRect rect,
               const BRect& updateRect, const rgb_color& base, uint32 flags,
               const BAlignment& alignment,
               const rgb_color* textColor = nullptr) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawLabel, view, label, rect, updateRect, base,
        flags, alignment, textColor);
}
void DrawLabel(BView* view, const char* label, const rgb_color& base,
               uint32 flags, const BPoint& where,
               const rgb_color* textColor = nullptr) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawLabel, view, label, base, flags, where,
        textColor);
}
void DrawLabel(BView* view, const char* label, const BBitmap* icon, BRect rect,
               const BRect& updateRect, const rgb_color& base, uint32 flags,
               const BAlignment& alignment,
               const rgb_color* textColor = nullptr) override {
    PYBIND11_OVERRIDE_PURE(
        void, BControlLook, DrawLabel, view, label, icon, rect, updateRect, base,
        flags, alignment, textColor);
}
void GetFrameInsets(frame_type frameType, uint32 flags, float& _left,
                    float& _top, float& _right, float& _bottom) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, GetFrameInsets, frameType, flags,
                           _left, _top, _right, _bottom);
}
void GetBackgroundInsets(background_type backgroundType, uint32 flags,
                         float& _left, float& _top, float& _right,
                         float& _bottom) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, GetBackgroundInsets,
                           backgroundType, flags, _left, _top, _right, _bottom);
}
void DrawButtonWithPopUpBackground(BView* view, BRect& rect,
                                   const BRect& updateRect,
                                   const rgb_color& base, uint32 flags = 0,
                                   uint32 borders = B_ALL_BORDERS,
                                   orientation orientation = B_HORIZONTAL) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonWithPopUpBackground,
                           view, rect, updateRect, base, flags, borders,
                           orientation);
}
void DrawButtonWithPopUpBackground(BView* view, BRect& rect,
                                   const BRect& updateRect, float radius,
                                   const rgb_color& base, uint32 flags = 0,
                                   uint32 borders = B_ALL_BORDERS,
                                   orientation orientation = B_HORIZONTAL) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonWithPopUpBackground,
                           view, rect, updateRect, radius, base, flags, borders,
                           orientation);
}
void DrawButtonWithPopUpBackground(BView* view, BRect& rect,
                                   const BRect& updateRect,
                                   float leftTopRadius, float rightTopRadius,
                                   float leftBottomRadius,
                                   float rightBottomRadius,
                                   const rgb_color& base, uint32 flags = 0,
                                   uint32 borders = B_ALL_BORDERS,
                                   orientation orientation = B_HORIZONTAL) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawButtonWithPopUpBackground,
                           view, rect, updateRect, leftTopRadius, rightTopRadius,
                           leftBottomRadius, rightBottomRadius, base, flags,
                           borders, orientation);
}
void DrawTabFrame(BView* view, BRect& rect, const BRect& updateRect,
                  const rgb_color& base, uint32 flags = 0, uint32 borders = B_ALL_BORDERS,
                  border_style borderStyle = B_FANCY_BORDER, uint32 side = B_TOP_BORDER) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawTabFrame, view, rect,
                           updateRect, base, flags, borders, borderStyle, side);
}
#ifdef TARGET_BETA5
void DrawScrollBarButton(BView* view, BRect rect, const BRect& updateRect,
                         const rgb_color& base, uint32 flags, int32 direction,
                         orientation orientation, bool down = false) {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollBarButton, view, rect,
                           updateRect, base, flags, direction, orientation, down);
}
#else
void DrawScrollBarButton(BView* view, BRect rect, const BRect& updateRect,
                         const rgb_color& base, const rgb_color& text, uint32 flags, int32 direction,
                         orientation orientation, bool down = false) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollBarButton, view, rect,
                           updateRect, base, text, flags, direction, orientation, down);
}
#endif
void DrawScrollBarThumb(BView* view, BRect& rect, const BRect& updateRect,
                        const rgb_color& base, uint32 flags,
                        orientation orientation, uint32 knobStyle = B_KNOB_NONE) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollBarThumb, view, rect,
                           updateRect, base, flags, orientation, knobStyle);
}
void DrawScrollBarBorder(BView* view, BRect rect, const BRect& updateRect,
                         const rgb_color& base, uint32 flags,
                         orientation orientation) override {
    PYBIND11_OVERRIDE_PURE(void, BControlLook, DrawScrollBarBorder, view, rect,
                           updateRect, base, flags, orientation);
}
float GetScrollBarWidth(orientation orientation = B_VERTICAL) override {
    PYBIND11_OVERLOAD(float, BControlLook, GetScrollBarWidth, orientation);
}
};

class MyClass {
public:
enum various {
		B_LEFT_BORDER		= 1 << 0,
		B_RIGHT_BORDER		= 1 << 1,
		B_TOP_BORDER		= 1 << 2,
		B_BOTTOM_BORDER		= 1 << 3,
		B_ALL_BORDERS		= B_LEFT_BORDER | B_RIGHT_BORDER | B_TOP_BORDER | B_BOTTOM_BORDER,
		
		B_LEFT_ARROW		= 0,
		B_RIGHT_ARROW		= 1,
		B_UP_ARROW			= 2,
		B_DOWN_ARROW		= 3,
		B_LEFT_UP_ARROW		= 4,
		B_RIGHT_UP_ARROW	= 5,
		B_RIGHT_DOWN_ARROW	= 6,
		B_LEFT_DOWN_ARROW	= 7,

		B_FOCUSED				= 1 << 0,
		B_CLICKED				= 1 << 1, // some controls activate on mouse up
		B_ACTIVATED				= 1 << 2,
		B_HOVER					= 1 << 3,
		B_DISABLED				= 1 << 4,
		B_DEFAULT_BUTTON		= 1 << 5,
		B_IGNORE_OUTLINE		= 1 << 6,
		B_PARTIALLY_ACTIVATED	= 1 << 7, // like B_ACTIVATED, but for tri-state
		B_FLAT					= 1 << 8, // flat look (e.g. button background)
		B_INVALID				= 1 << 9, // invalid value, use B_FAILURE_COLOR
		B_IS_CONTROL			= 1 << 10, // use control colors
		B_BLEND_FRAME			= 1 << 16,

		B_KNOB_NONE = 0,
		B_KNOB_DOTS,
		B_KNOB_LINES
};
//    static void exportEnum(py::module& m) {
//        m.attr("B_KNOB_NONE") = py::int_(B_KNOB_NONE);
//        m.attr("B_KNOB_DOTS") = py::int_(B_KNOB_DOTS);
//        m.attr("B_KNOB_LINES") = py::int_(B_KNOB_LINES);
//        
//    }
};



PYBIND11_MODULE(ControlLook,m)
{
	

/*py::enum_<frame_type>(m, "frame_type", "")
.value("B_BUTTON_FRAME", frame_type::B_BUTTON_FRAME, "")
.value("B_GROUP_FRAME", frame_type::B_GROUP_FRAME, "")
.value("B_MENU_FIELD_FRAME", frame_type::B_MENU_FIELD_FRAME, "")
.value("B_SCROLL_VIEW_FRAME", frame_type::B_SCROLL_VIEW_FRAME, "")
.value("B_TEXT_CONTROL_FRAME", frame_type::B_TEXT_CONTROL_FRAME, "")
.export_values();*/

py::enum_<BControlLook::frame_type>(m, "frame_type")
        .value("B_BUTTON_FRAME", BControlLook::frame_type::B_BUTTON_FRAME)
        .value("B_GROUP_FRAME", BControlLook::frame_type::B_GROUP_FRAME)
        .value("B_MENU_FIELD_FRAME", BControlLook::frame_type::B_MENU_FIELD_FRAME)
        .value("B_SCROLL_VIEW_FRAME", BControlLook::frame_type::B_SCROLL_VIEW_FRAME)
        .value("B_TEXT_CONTROL_FRAME", BControlLook::frame_type::B_TEXT_CONTROL_FRAME);

py::enum_<BControlLook::background_type>(m, "background_type")
            .value("B_BUTTON_BACKGROUND", BControlLook::background_type::B_BUTTON_BACKGROUND)
            .value("B_BUTTON_WITH_POP_UP_BACKGROUND", BControlLook::background_type::B_BUTTON_WITH_POP_UP_BACKGROUND)
            .value("B_MENU_BACKGROUND", BControlLook::background_type::B_MENU_BACKGROUND)
            .value("B_MENU_BAR_BACKGROUND", BControlLook::background_type::B_MENU_BAR_BACKGROUND)
            .value("B_MENU_FIELD_BACKGROUND", BControlLook::background_type::B_MENU_FIELD_BACKGROUND)
            .value("B_MENU_ITEM_BACKGROUND", BControlLook::background_type::B_MENU_ITEM_BACKGROUND)
            .value("B_HORIZONTAL_SCROLL_BAR_BACKGROUND", BControlLook::background_type::B_HORIZONTAL_SCROLL_BAR_BACKGROUND)
            .value("B_VERTICAL_SCROLL_BAR_BACKGROUND", BControlLook::background_type::B_VERTICAL_SCROLL_BAR_BACKGROUND);
            
py::enum_<MyClass::various>(m, "BControlLookEnum")
.value("B_LEFT_BORDER", MyClass::various::B_LEFT_BORDER)
.value("B_RIGHT_BORDER", MyClass::various::B_RIGHT_BORDER)
.value("B_TOP_BORDER", MyClass::various::B_TOP_BORDER)
.value("B_BOTTOM_BORDER", MyClass::various::B_BOTTOM_BORDER)
.value("B_ALL_BORDERS", MyClass::various::B_ALL_BORDERS)
.value("B_LEFT_ARROW", MyClass::various::B_LEFT_ARROW)
.value("B_RIGHT_ARROW", MyClass::various::B_RIGHT_ARROW)
.value("B_UP_ARROW", MyClass::various::B_UP_ARROW)
.value("B_DOWN_ARROW", MyClass::various::B_DOWN_ARROW)
.value("B_LEFT_UP_ARROW", MyClass::various::B_LEFT_UP_ARROW)
.value("B_RIGHT_UP_ARROW", MyClass::various::B_RIGHT_UP_ARROW)
.value("B_RIGHT_DOWN_ARROW", MyClass::various::B_RIGHT_DOWN_ARROW)
.value("B_LEFT_DOWN_ARROW", MyClass::various::B_LEFT_DOWN_ARROW)
.value("B_FOCUSED", MyClass::various::B_FOCUSED)
.value("B_CLICKED", MyClass::various::B_CLICKED)
.value("B_ACTIVATED", MyClass::various::B_ACTIVATED)
.value("B_HOVER", MyClass::various::B_HOVER)
.value("B_DISABLED", MyClass::various::B_DISABLED)
.value("B_DEFAULT_BUTTON", MyClass::various::B_DEFAULT_BUTTON)
.value("B_IGNORE_OUTLINE", MyClass::various::B_IGNORE_OUTLINE)
.value("B_PARTIALLY_ACTIVATED", MyClass::various::B_PARTIALLY_ACTIVATED)
.value("B_FLAT", MyClass::various::B_FLAT)
.value("B_INVALID", MyClass::various::B_INVALID)
.value("B_IS_CONTROL", MyClass::various::B_IS_CONTROL)
.value("B_BLEND_FRAME", MyClass::various::B_BLEND_FRAME)
.value("B_KNOB_NONE", MyClass::various::B_KNOB_NONE)
.value("B_KNOB_DOTS", MyClass::various::B_KNOB_DOTS)
.value("B_KNOB_LINES", MyClass::various::B_KNOB_LINES)
.export_values();
/*
m.attr("B_LEFT_BORDER") = BControlLook::B_LEFT_BORDER;
m.attr("B_RIGHT_BORDER") = BControlLook::B_RIGHT_BORDER;
m.attr("B_TOP_BORDER") = BControlLook::B_TOP_BORDER;
m.attr("B_BOTTOM_BORDER") = BControlLook::B_BOTTOM_BORDER;
m.attr("B_ALL_BORDERS") = BControlLook::B_ALL_BORDERS;
m.attr("B_LEFT_ARROW") = BControlLook::B_LEFT_ARROW;
m.attr("B_RIGHT_ARROW") = BControlLook::B_RIGHT_ARROW;
m.attr("B_UP_ARROW") = BControlLook::B_UP_ARROW;
m.attr("B_DOWN_ARROW") = BControlLook::B_DOWN_ARROW;
m.attr("B_LEFT_UP_ARROW") = BControlLook::B_LEFT_UP_ARROW;
m.attr("B_RIGHT_UP_ARROW") = BControlLook::B_RIGHT_UP_ARROW;
m.attr("B_RIGHT_DOWN_ARROW") = BControlLook::B_RIGHT_DOWN_ARROW;
m.attr("B_LEFT_DOWN_ARROW") = BControlLook::B_LEFT_DOWN_ARROW;
m.attr("B_FOCUSED") = BControlLook::B_FOCUSED;
m.attr("B_CLICKED") = BControlLook::B_CLICKED;
m.attr("B_ACTIVATED") = BControlLook::B_ACTIVATED;
m.attr("B_HOVER") = BControlLook::B_HOVER;
m.attr("B_DISABLED") = BControlLook::B_DISABLED;
m.attr("B_DEFAULT_BUTTON") = BControlLook::B_DEFAULT_BUTTON;
m.attr("B_IGNORE_OUTLINE") = BControlLook::B_IGNORE_OUTLINE;
m.attr("B_PARTIALLY_ACTIVATED") = BControlLook::B_PARTIALLY_ACTIVATED;
m.attr("B_FLAT") = BControlLook::B_FLAT;
m.attr("B_INVALID") = BControlLook::B_INVALID;
m.attr("B_IS_CONTROL") = BControlLook::B_IS_CONTROL;
m.attr("B_BLEND_FRAME") = BControlLook::B_BLEND_FRAME;
m.attr("B_KNOB_NONE") = BControlLook::B_KNOB_NONE;
m.attr("B_KNOB_DOTS") = BControlLook::B_KNOB_DOTS;
m.attr("B_KNOB_LINES") = BControlLook::B_KNOB_LINES;*/

m.attr("B_LEFT_BORDER") = 1 << 0;
m.attr("B_RIGHT_BORDER") = 1 << 1;
m.attr("B_TOP_BORDER") = 1 << 2;
m.attr("B_BOTTOM_BORDER") = 1 << 3;
m.attr("B_ALL_BORDERS") = py::int_(BControlLook::B_LEFT_BORDER | BControlLook::B_RIGHT_BORDER | BControlLook::B_TOP_BORDER | BControlLook::B_BOTTOM_BORDER);
m.attr("B_LEFT_ARROW") = 0;
m.attr("B_RIGHT_ARROW") = 1;
m.attr("B_UP_ARROW") = 2;
m.attr("B_DOWN_ARROW") = 3;
m.attr("B_LEFT_UP_ARROW") = 4;
m.attr("B_RIGHT_UP_ARROW") = 5;
m.attr("B_RIGHT_DOWN_ARROW") = 6;
m.attr("B_LEFT_DOWN_ARROW") = 7;
m.attr("B_FOCUSED") = 1 << 0;
m.attr("B_CLICKED") = 1 << 1;
m.attr("B_ACTIVATED") = 1 << 2;
m.attr("B_HOVER") = 1 << 3;
m.attr("B_DISABLED") = 1 << 4;
m.attr("B_DEFAULT_BUTTON") = 1 << 5;
m.attr("B_IGNORE_OUTLINE") = 1 << 6;
m.attr("B_PARTIALLY_ACTIVATED") = 1 << 7;
m.attr("B_FLAT") = 1 << 8;
m.attr("B_INVALID") = 1 << 9;
m.attr("B_IS_CONTROL") = 1 << 10;
m.attr("B_BLEND_FRAME") = 1 << 16;
m.attr("B_KNOB_NONE") = 0;
m.attr("B_KNOB_DOTS") = 1;
m.attr("B_KNOB_LINES") = 2;


py::class_<BControlLook,PyBControlLook>(m, "BControlLook")
.def(py::init(), "")
.def("DefaultLabelAlignment", &BControlLook::DefaultLabelAlignment, "")
.def("DefaultLabelSpacing", &BControlLook::DefaultLabelSpacing, "")
.def("DefaultItemSpacing", &BControlLook::DefaultItemSpacing, "")
.def_static("ComposeSpacing", &BControlLook::ComposeSpacing, "", py::arg("spacing"))
.def_static("ComposeIconSize", &BControlLook::ComposeIconSize, "", py::arg("size"))
.def("Flags", &BControlLook::Flags, "", py::arg("control"))
.def("DrawButtonFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & background,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawButtonFrame(view, rect, updateRect, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawButtonFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,const rgb_color & background,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawButtonFrame(view, rect, updateRect, radius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawButtonFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,const rgb_color & background,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawButtonFrame(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawButtonBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonBackground(view, rect, updateRect, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonBackground(view, rect, updateRect, radius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonBackground(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawMenuBarBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuBarBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawMenuFieldFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & background,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldFrame(view, rect, updateRect, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawMenuFieldFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,const rgb_color & background,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldFrame(view, rect, updateRect, radius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawMenuFieldFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,const rgb_color & background,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldFrame(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,bool popupIndicator,uint32 flags=0) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, base, popupIndicator, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("popupIndicator"), py::arg("flags")=0)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,bool popupIndicator,uint32 flags=0) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, radius, base, popupIndicator, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("popupIndicator"), py::arg("flags")=0)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,bool popupIndicator,uint32 flags=0) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, popupIndicator, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("popupIndicator"), py::arg("flags")=0)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawMenuBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawMenuItemBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuItemBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawStatusBar", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & barColor,float progressPosition) {
    BRect  rect;
    self.DrawStatusBar(view, rect, updateRect, base, barColor, progressPosition);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("barColor"), py::arg("progressPosition"))
.def("DrawCheckBox", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0) {
    BRect  rect;
    self.DrawCheckBox(view, rect, updateRect, base, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0)
.def("DrawRadioButton", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0) {
    BRect  rect;
    self.DrawRadioButton(view, rect, updateRect, base, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0)
.def("DrawScrollBarBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags,orientation orientation) {
    BRect  rect1;
BRect  rect2;
    self.DrawScrollBarBackground(view, rect1, rect2, updateRect, base, flags, orientation);
    return std::make_tuple(rect1,rect2);
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawScrollBarBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags,orientation orientation) {
    BRect  rect;
    self.DrawScrollBarBackground(view, rect, updateRect, base, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawScrollViewFrame", [](BControlLook& self,BView * view,const BRect & updateRect,BRect verticalScrollBarFrame,BRect horizontalScrollBarFrame,const rgb_color & base,border_style borderStyle,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawScrollViewFrame(view, rect, updateRect, verticalScrollBarFrame, horizontalScrollBarFrame, base, borderStyle, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("verticalScrollBarFrame"), py::arg("horizontalScrollBarFrame"), py::arg("base"), py::arg("borderStyle"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawArrowShape", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 direction,uint32 flags=0,float tint=B_DARKEN_MAX_TINT) {
    BRect  rect;
    self.DrawArrowShape(view, rect, updateRect, base, direction, flags, tint);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("direction"), py::arg("flags")=0, py::arg("tint")=B_DARKEN_MAX_TINT)
.def("SliderBarColor", &BControlLook::SliderBarColor, "", py::arg("base"))
.def("DrawSliderBar", py::overload_cast<BView *, BRect, const BRect &, const rgb_color &, rgb_color, rgb_color, float, uint32, orientation>(&BControlLook::DrawSliderBar), "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("leftFillColor"), py::arg("rightFillColor"), py::arg("sliderScale"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderBar", py::overload_cast<BView *, BRect, const BRect &, const rgb_color &, rgb_color, uint32, orientation>(&BControlLook::DrawSliderBar), "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("fillColor"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderThumb", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderThumb(view, rect, updateRect, base, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderTriangle", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderTriangle(view, rect, updateRect, base, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderTriangle", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & fill,uint32 flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderTriangle(view, rect, updateRect, base, fill, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("fill"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderHashMarks", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,int count,hash_mark_location location,uint32 flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderHashMarks(view, rect, updateRect, base, count, location, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("count"), py::arg("location"), py::arg("flags"), py::arg("orientation"))
.def("DrawActiveTab", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,uint32 side=MyClass::various::B_TOP_BORDER,int index=0,int selected=- 1,int first=0,int last=0) {
    BRect  rect;
    self.DrawActiveTab(view, rect, updateRect, base, flags, borders, side, index, selected, first, last);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("side")=MyClass::various::B_TOP_BORDER, py::arg("index")=0, py::arg("selected")=- 1, py::arg("first")=0, py::arg("last")=0)
.def("DrawInactiveTab", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,uint32 side=MyClass::various::B_TOP_BORDER,int index=0,int selected=- 1,int first=0,int last=0) {
    BRect  rect;
    self.DrawInactiveTab(view, rect, updateRect, base, flags, borders, side, index, selected, first, last);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("side")=MyClass::various::B_TOP_BORDER, py::arg("index")=0, py::arg("selected")=- 1, py::arg("first")=0, py::arg("last")=0)
.def("DrawSplitter", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,orientation orientation,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawSplitter(view, rect, updateRect, base, orientation, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("orientation"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawBorder", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,border_style borderStyle,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawBorder(view, rect, updateRect, base, borderStyle, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("borderStyle"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawRaisedBorder", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawRaisedBorder(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawGroupFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawGroupFrame(view, rect, updateRect, base, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawTextControlBorder", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS) {
    BRect  rect;
    self.DrawTextControlBorder(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS)
.def("DrawLabel", py::overload_cast<BView *, const char *, BRect, const BRect &, const rgb_color &, uint32, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, BRect, const BRect &, const rgb_color &, uint32, const BAlignment &, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("alignment"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, const rgb_color &, uint32, const BPoint &, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("base"), py::arg("flags"), py::arg("where"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, const BBitmap *, BRect, const BRect &, const rgb_color &, uint32, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("icon"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, const BBitmap *, BRect, const BRect &, const rgb_color &, uint32, const BAlignment &, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("icon"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("alignment"), py::arg("textColor")=NULL)
.def("GetFrameInsets", [](BControlLook& self,BControlLook::frame_type frameType,uint32 flags) {
    float  _left;
float  _top;
float  _right;
float  _bottom;
    self.GetFrameInsets(frameType, flags, _left, _top, _right, _bottom);
    return std::make_tuple(_left,_top,_right,_bottom);
}
, "", py::arg("frameType"), py::arg("flags"))
.def("GetBackgroundInsets", [](BControlLook& self,BControlLook::background_type backgroundType,uint32 flags) {
    float  _left;
float  _top;
float  _right;
float  _bottom;
    self.GetBackgroundInsets(backgroundType, flags, _left, _top, _right, _bottom);
    return std::make_tuple(_left,_top,_right,_bottom);
}
, "", py::arg("backgroundType"), py::arg("flags"))
.def("GetInsets", [](BControlLook& self,BControlLook::frame_type frameType,BControlLook::background_type backgroundType,uint32 flags) {
    float  _left;
float  _top;
float  _right;
float  _bottom;
    self.GetInsets(frameType, backgroundType, flags, _left, _top, _right, _bottom);
    return std::make_tuple(_left,_top,_right,_bottom);
}
, "", py::arg("frameType"), py::arg("backgroundType"), py::arg("flags"))
.def("DrawButtonWithPopUpBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonWithPopUpBackground(view, rect, updateRect, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonWithPopUpBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonWithPopUpBackground(view, rect, updateRect, radius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonWithPopUpBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonWithPopUpBackground(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("SetBackgroundInfo", &BControlLook::SetBackgroundInfo, "", py::arg("backgroundInfo"))
.def("DrawTabFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags=0,uint32 borders=MyClass::various::B_ALL_BORDERS,border_style borderStyle=B_FANCY_BORDER,uint32 side=MyClass::various::B_TOP_BORDER) {
    BRect  rect;
    self.DrawTabFrame(view, rect, updateRect, base, flags, borders, borderStyle, side);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=MyClass::various::B_ALL_BORDERS, py::arg("borderStyle")=B_FANCY_BORDER, py::arg("side")=MyClass::various::B_TOP_BORDER)
#ifdef TARGET_BETA5
.def("DrawScrollBarButton", &BControlLook::DrawScrollBarButton, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("direction"), py::arg("orientation"), py::arg("down")=false)
#else
.def("DrawScrollBarButton", &BControlLook::DrawScrollBarButton, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("text"), py::arg("flags"), py::arg("direction"), py::arg("orientation"), py::arg("down")=false)
#endif
.def("DrawScrollBarThumb", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,uint32 flags,orientation orientation,uint32 knobStyle=MyClass::various::B_KNOB_NONE) {
    BRect  rect;
    self.DrawScrollBarThumb(view, rect, updateRect, base, flags, orientation, knobStyle);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"), py::arg("knobStyle")=MyClass::various::B_KNOB_NONE)
.def("DrawScrollBarBorder", &BControlLook::DrawScrollBarBorder, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("GetScrollBarWidth", &BControlLook::GetScrollBarWidth, "", py::arg("orientation")=B_VERTICAL)
.def_static("ShouldDraw", &BControlLook::ShouldDraw, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"))
;

//m.attr("BControlLook") = BControlLook;

//m.attr("be_control_look") = be_control_look;
//m.attr("be_control_look") = be_control_look;
//m.def("instantiate_control_look", &instantiate_control_look, "", py::arg("id")); //resolve symbol "instantiate_control_look" returned: -2147478780

}
