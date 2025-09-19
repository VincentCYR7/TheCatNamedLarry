#pragma once

#include <Siv3D.hpp>

class KingMoveManager
{
	public:
		// 現在の残り移動時間
		double _timeFramePerSec;
		
	private:
		// 王の移動速度
		double _scrollSpeedPerSec;

		// 王の総移動時間
		double _kingMoveTimeSec;

		// 王のX座標
		double _kingXPosition;

		// 王の最大HP
		int32 _kingMaxHP;

		// 王のHP
		int32 _kingHP;

		// 王が受けるダメージ
		int32 _kingDamage;

		// 穴に入っているか
		bool _isInsideTheHole = false;

		// 王の座標のオフセット
		const double _kingPosOffset = 100;

		const Texture king{U"Assets/king.png"};

		const Texture queen{U"Assets/queen.png" };

		const Rect _gaugeBackImage{ 200, 50, 800, 50 };

		RectF _hpGaugebackImage;

		const double _hpGaugebackImageWidth = 100;

		const double _hpGaugebackImageHeight = 30;

		const double _invisibleSec = 2.0;

		double _invisibleCount = 0;

		std::vector<std::function<void()>> _winDelegates;

		std::vector<std::function<void()>> _loseDelegates;

		bool _hasWin = false;

		bool _hasLose = false;

	public:
		Circle collider{ 400, 300, 40 };

		bool fallen = false;

		KingMoveManager(double kingXPosition, double scrollSpeed, double gamePlayDuration, int32 kingHP, int32 kingDamage);
		~KingMoveManager();
		
		void AddWinEvent(std::function<void()> func);

		void InvokeWinEvent();

		void AddLoseEvent(std::function<void()> func);

		void InvokeLoseEvent();

		bool IsInsideTheHole();

		void FellIntoTheHole();

		void CameOutOfTheHole();

		void OnKingDamaged();

		void Update();

		void Draw();

		char ReturnGameStatus();

		Vec2 queenPos;
};