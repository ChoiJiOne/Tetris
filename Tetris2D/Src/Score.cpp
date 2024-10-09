#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Score.h"

Score::Score()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font32");

	text_ = L"SCORE";
	Vec2f textSize;
	font_->MeasureText(text_, textSize.x, textSize.y);
	
	Vec2f textPos = Vec2f(195.0f, 0.0f);
	textPos_ = textPos + Vec2f(-textSize.x * 0.5f, +textSize.y * 0.5f);
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	scoreText_ = GameUtils::PrintF(L"%d", score_);

	Vec2f scoreTextSize;
	font_->MeasureText(scoreText_, scoreTextSize.x, scoreTextSize.y);

	Vec2f scoreTextPos = Vec2f(195.0f, -50.0f);
	scoreTextPos_ = scoreTextPos + Vec2f(-scoreTextSize.x * 0.5f, +scoreTextSize.y * 0.5f);
	scoreTextColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	outline_ = Rect2D(Vec2f(195.0f, -50.0f), Vec2f(120.0f, 50.0f));
	outlineColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	bIsInitialized_ = true;
}

Score::~Score()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Score::Tick(float deltaSeconds)
{
	if (bIsUpdateScore_)
	{
		scoreText_ = GameUtils::PrintF(L"%d", score_);

		Vec2f scoreTextSize;
		font_->MeasureText(scoreText_, scoreTextSize.x, scoreTextSize.y);

		Vec2f scoreTextPos = Vec2f(195.0f, -50.0f);
		scoreTextPos_ = scoreTextPos + Vec2f(-scoreTextSize.x * 0.5f, +scoreTextSize.y * 0.5f);

		bIsUpdateScore_ = false;
	}
}

void Score::Render()
{
	RenderManager2D::Get().DrawString(font_, text_, textPos_, textColor_);
	RenderManager2D::Get().DrawString(font_, scoreText_, scoreTextPos_, scoreTextColor_);
	RenderManager2D::Get().DrawRoundRectWireframe(outline_.center, outline_.size.x, outline_.size.y, 10.0f, outlineColor_, 0.0f);
}

void Score::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void Score::SetScore(int32_t score)
{
	score_ = score;
	bIsUpdateScore_ = true;
}