#pragma once
#include "../SDK/Render/MinecraftUIRenderContext.h"

class RenderUtils
{
public:
	static void fillRectangle(Vector4<float> pos, UIColor col, float alpha) {
		Address::getRenderContext()->fillRectangle(Vector4<float>(pos.x, pos.z, pos.y, pos.w), col, alpha);
	}

	static float getTextWidth(std::string* str, float size)
	{
		TextHolder text(*str);
		return Address::getRenderContext()->getLineLength(Address::getFont(), &text, size, true);
	}

	static void drawText(Vector2<float> pos, std::string* str, UIColor color, float size, float alpha, bool shadow)
	{
		TextHolder text(*str);
		static CaretMeasureData black = CaretMeasureData(20, false);

		float tPos[4] = { pos.x, pos.x + 1000, pos.y, pos.y + 1000 };
		TextMeasureData data = TextMeasureData(size, shadow);

		Address::getRenderContext()->drawText(Address::getFont(), tPos, &text, color.arr, alpha, 0, &data, &black);
	}

	/*static void renderImage(std::string filePath, Vector2<float> ImagePos, Vector2<float> ImageDimension, Type type = External)
	{
		renderContext->getTexture(new TexturePtr(), new ResourceLocation(type, filePath));
		renderContext->drawImage(new TexturePtr(), &ImagePos, &ImageDimension, Vector2<float>(0.f, 0.f), Vector2<float>(1.f, 1.f));
	}*/
};