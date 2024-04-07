#pragma once

class ComponentRenderBatch;
class HashedString;

#include "TextMeasureData.h"
#include "CaretMeasureData.h"

class TexturePtr // TextureData's class
{
private:
    char pad_0x0[0x18];
    struct PathStruct // FilePath's sturct
    {
        char pad_0x0[0x18]; // The offset for filePath string
        TextHolder filePath; // filePath string
    }
    *ptrToPath;
    char pad_0x0038[0x20];
public:
    TextHolder getFilePath() const // getFilePath from PathStruct
    {
        return ptrToPath->filePath;
    }
};

class NinesliceInfo { // NinesliceInfo
private:
    char pad_0x0000[0xFF]; //0x0000
};

class MinecraftUIRenderContext {
public:
    void* ClientInstance; // ClientInstance class should be here

private:
    virtual void Destructor();
public:
    virtual float getLineLength(FontRepos* font, TextHolder* str, float measureCalculation, bool calculateWidth);
private:
    virtual int getTextAlpha();
    virtual void setTextAlpha();
    virtual void drawDebugText();
public:
    virtual void drawText(FontRepos* font, const float* pos, TextHolder* str, const float* colour, float, float alinM, const TextMeasureData* textMeasureData, const CaretMeasureData* caretMeasureData);
    virtual void flushText(float flushDelta);
public:
    virtual void drawImage(TexturePtr*, Vector2<float>* ImagePos, Vector2<float>* ImageDimension, Vector2<float> const& uvPos, Vector2<float> const& uvSize);
    virtual void drawNineslice(TexturePtr* const& texturePtr, NinesliceInfo NinesliceInfo);
    virtual void flushImages();
    virtual void beginSharedMeshBatch(uintptr_t ComponentRenderBatch);
    virtual void endSharedMeshBatch(float timeSinceLastFlush);
public:
    virtual void drawRectangle(Vector4<float> const& rect, UIColor const& colour, float alpha, int width);
    virtual void fillRectangle(Vector4<float> const& rect, UIColor const& colour, float alpha);
public:
    virtual auto increaseStencilRef() -> void {};
    virtual auto decreaseStencilRef() -> void {};
    virtual auto resetStencilRef() -> void {};
    virtual auto fillRectangleStencil(Vector4<float> const& position) -> void {};
    virtual auto enableScissorTest(Vector4<float> const& position) -> void {};
    virtual auto disableScissorTest() -> void {};
    virtual auto setClippingRectangle(Vector4<float> const& position) -> void {};
    virtual auto setFullClippingRectangle() -> void {};
    virtual auto saveCurrentClippingRectangle() -> void {};
    virtual auto restoreSavedClippingRectangle() -> void {};
    virtual auto getFullClippingRectangle() -> int {};
    virtual auto updateCustom(uintptr_t a1) -> void {};
    virtual auto renderCustom(uintptr_t a1, int a2, Vector4<float> const& position) -> void {};
    virtual auto cleanup() -> void {};
    virtual auto removePersistentMeshes() -> void {};
    virtual auto getTexture(class TexturePtr* texture, void* resourceLocation) -> int {};
    virtual auto getZippedTexture(class TexturePtr* Path, class TexturePtr* ResourceLocation, bool a3) -> int {};
    virtual auto unloadTexture(class TexturePtr* ResourceLocation) -> void {};
    virtual auto getUITextureInfo(class TexturePtr* ResourceLocation, bool a2) -> int {};
    virtual auto touchTexture(class TexturePtr* ResourceLocation) -> void {};
    virtual auto getMeasureStrategy(Vector2<float> const&) -> int {};
    virtual auto snapImageSizeToGrid(Vector2<float> const&) -> void {};
    virtual auto snapImagePositionToGrid(Vector2<float> const&) -> void {};
    virtual auto notifyImageEstimate(ULONG) -> void {};
};