#pragma once

// Includes
#include "../../SDK/Render/MinecraftUIRenderContext.h"

// Declare a void pointer(Empty object) called onRender which is the CallBack for renderDetourHook.
void* onRender; // Defined an orignal for RenderDetour.

// Declare a void pointer(Empty object) called onDrawText which is the CallBack for onDrawTextDetour.
__int64* onDrawText; // Defined an orignal for onDrawTextDetour.
// Declare a void pointer(Empty object) called onDrawImage which is the CallBack for onDrawImageDetour.
__int64* onDrawImage; // Defined an orignal for onDrawImageDetour.
// Declare a void pointer(Empty object) called onDrawNineSlice which is the CallBack for onDrawNineSliceHook.
__int64* onDrawNineSlice; // Defined an orignal for onDrawNineSliceHook.

// Declare a variable called layerCounter and initialize it to 0
int layerCounter = 0; // Defined an orignal for RenderDetour.

#pragma region onDrawText

// MinecraftUIRenderContext, FontRepos, TextPos, TextHolder, UIColor, Alpha, AlinM, TextMeasureData, CaretMeasureData
void onDrawTextDetour(MinecraftUIRenderContext* _this, FontRepos* font, Vector4<float> const& pos, TextHolder* str, UIColor const& colour, float alpha, float alinM, TextMeasureData const& textdata, CaretMeasureData const& caretdata) {
    Address::Font = font;

    // Inside our functiion we're calling the original code that was there/the original function we hooked so the games behavior doesn't change.
    Utils::CallFunc<void, MinecraftUIRenderContext*, FontRepos*, Vector4<float> const&, TextHolder*, UIColor const&, float, float, TextMeasureData const&, CaretMeasureData const&>(
        onDrawText, _this, font, pos, str, colour, alpha, alinM, textdata, caretdata);
}

#pragma endregion
#pragma region onDrawImage

// MinecraftUIRenderContext, TexturePtr, ImagePos, ImageDimesnion, UvPos, UvSize
void onDrawImageDetour(MinecraftUIRenderContext* ctx, TexturePtr* path, Vector2<float>& ImagePos, Vector2<float>& a3, Vector2<float>& a4, Vector2<float>& a5) {
    if (strcmp(path->getFilePath().getText(), "textures/ui/title") == 0) {
        //return;
        // Declare a UIColor object called color and initialize it with the values 11, 11, 11, 255
        UIColor color = UIColor{ 11, 11, 11, 255 };

        // Declare a Vector4 object called rectPos and initialize it with the values { 25, 25 }, { 25, 25 }
        Vector4<float> rectPos({ 0, 0 }, { 1900, 1900 });

        // Call the fillRectangle function on ctx, passing in rectPos and color as arguments
        ctx->fillRectangle(rectPos, color, color.a);

        if (Address::getFont() == nullptr)
            return;

        std::string str("Frost");

        float strSize = 6;
        float width = RenderUtils::getTextWidth(&str, strSize) / 2;

        Vector2<float> titlePos = Vector2<float>((ImagePos.x + (a3.x / 2)) - width, ImagePos.y);

        RenderUtils::drawText(titlePos, &str, UIColor(255, 255, 255), strSize, 1, true);

        // Hide the minecraft title.
        return;
    }

    // Inside our functiion we're calling the original code that was there/the original function we hooked so the games behavior doesn't change.
    Utils::CallFunc<void*, MinecraftUIRenderContext*, TexturePtr*, Vector2<float>&, Vector2<float>&, Vector2<float>&, Vector2<float>&>(
        onDrawImage, ctx, path, ImagePos, a3, a4, a5);
}

#pragma endregion
#pragma region onDrawNineSlice

// MinecraftUIRenderContext, TexturePtr, nineSliceInfo
void onDrawNineSliceDetour(MinecraftUIRenderContext* _this, TexturePtr* texturePtr, NinesliceInfo* nineSliceInfo) {
    float* x = reinterpret_cast<float*>((__int64)nineSliceInfo);
    float* y = reinterpret_cast<float*>((__int64)nineSliceInfo + 0x4);
    float* z = reinterpret_cast<float*>((__int64)nineSliceInfo + 0x60); // funny cuh offset
    float* w = reinterpret_cast<float*>((__int64)nineSliceInfo + 0x64);
    Vector4<float> position(*x, *y, *z, *w);

    if (strcmp(texturePtr->getFilePath().getText(), "textures/ui/hotbar_start_cap") == 0 || (strcmp(texturePtr->getFilePath().getText(), "textures/ui/hotbar_end_cap") == 0)) {
        return;
    }

    // Inside our functiion we're calling the original code that was there/the original function we hooked so the games behavior doesn't change.
    Utils::CallFunc<void*, MinecraftUIRenderContext*, TexturePtr*, NinesliceInfo*>(
        onDrawNineSlice, _this, texturePtr, nineSliceInfo);
}

#pragma endregion

void renderDetourHook(void* __this, MinecraftUIRenderContext* ctx) { // ScreenContext, MinecraftUIRenderContext
    // Call the function at the address stored in onRender, passing in __this and ctx as arguments
    Utils::CallFunc<void*, void*, MinecraftUIRenderContext*>(
        onRender, __this, ctx
    );

    // Initialize RenderContext for Address
    Address::renderContext = ctx; // set CTX

    // MinecraftUIRenderContext VTable
    auto vtable = *(uintptr_t**)ctx;
    // Make a bool for tryDrawImage
    static bool tryHookDrawText = false;
    static bool tryHookDrawImage = false;
    static bool tryHookDrawNineSlice = false;

    if (!tryHookDrawText) {
        // Hook drawText from MinecraftUIRenderContext's VTable
        tryHookDrawText = Utils::HookFunction((void*)vtable[5], (void*)&onDrawTextDetour, &onDrawText, "DrawText");
    }

    if (!tryHookDrawImage) {
        // Hook drawImage from MinecraftUIRenderContext's VTable
        tryHookDrawImage = Utils::HookFunction((void*)vtable[7], (void*)&onDrawImageDetour, &onDrawImage, "DrawImage");
    }

    if (!tryHookDrawNineSlice) {
        // Hook drawImage from MinecraftUIRenderContext's VTable
        tryHookDrawNineSlice = Utils::HookFunction((void*)vtable[8], (void*)&onDrawNineSliceDetour, &onDrawNineSlice, "DrawNineSlice");
    }
}

class RenderContextHook : public FuncHook {
public:
    bool Initialize() override
    {
        // 2873 is the size of the machine code (Excluding variables) at the time im making this

        // Find the address of the function specified by the signature {SIG} and store it in a void pointer called renderAddr
        // Using the utils class findSig function to locate the address of the signature

        // TickAndRenderUI string
        void* renderAddr = Utils::findSig("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 54 24 ? 4C");

        // Give it the address/ptr to the renderDetour function.
        // Give it the detour ptr and then the original callback ptr.

        // Usage: (Sig/Address/Offset, Detour, Original Callback).
        // Don't forget to return its result.

        // Attempt to hook the function at the address stored in renderAddr by replacing it with the address of renderDetour and store the original function's address in onRender
        return Utils::HookFunction(renderAddr, (void*)&renderDetourHook, &onRender, "RenderContext");

        return true;
    }

    static RenderContextHook& Instance() { // a class setup function called Instance.
        static RenderContextHook instance;
        return instance;
    }
};