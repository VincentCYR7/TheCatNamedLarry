#include "KingMoveManager.h"

KingMoveManager::KingMoveManager(double kingXPosition, double scrollSpeed, double gamePlayDuration, int32 kingHP, int32 kingDamage) {
	_kingXPosition = kingXPosition;
	_scrollSpeedPerSec = scrollSpeed;
	_kingMoveTimeSec = gamePlayDuration;
	_timeFramePerSec = _kingMoveTimeSec;
	_kingMaxHP = kingHP;
	_kingHP = _kingMaxHP;
	_kingDamage = kingDamage;
	_hpGaugebackImage = { kingXPosition - (_hpGaugebackImageWidth / 2), Scene::Height() / 2 - 100, _hpGaugebackImageWidth, _hpGaugebackImageHeight };
	queenPos = Vec2((_timeFramePerSec * _scrollSpeedPerSec) + _kingXPosition + _kingPosOffset, Scene::Height() / 2);
}

void KingMoveManager::AddWinEvent(std::function<void()> func)
{
	_winDelegates.push_back(func);
}

void KingMoveManager::InvokeWinEvent()
{
	if (_hasWin) return;
	_hasWin = true;
	for (auto& delegate : _winDelegates)
	{
		delegate();
	}
}

void KingMoveManager::AddLoseEvent(std::function<void()> func)
{
	_loseDelegates.push_back(func);
}

void KingMoveManager::InvokeLoseEvent()
{
	if (_hasWin) return;
	_hasLose = true;
	for (auto& delegate : _loseDelegates)
	{
		delegate();
	}
}

bool KingMoveManager::IsInsideTheHole() {
	return fallen;
}

void KingMoveManager::FellIntoTheHole() {
	fallen = true;
}

void KingMoveManager::CameOutOfTheHole() {
	fallen = false;
}

void KingMoveManager::OnKingDamaged() {
	if (fallen) return;
	//if (_invisibleCount > 0) return;
	//_invisibleCount = _invisibleSec;
	_kingHP -= _kingDamage;
}

void KingMoveManager::Update() {
	//Print(_invisibleCount);
	//Print(_kingHP);
	//Console << _timeFramePerSec;
	if (_invisibleCount > 0)
		_invisibleCount -= Scene::DeltaTime();
	if (!fallen && _timeFramePerSec > 0)
		_timeFramePerSec -= Scene::DeltaTime();
	if (_invisibleCount > 0)
		_invisibleCount -= Scene::DeltaTime();
	collider.setPos(Vec2{_kingXPosition, Scene::Height() / 2});
	if (_kingHP <= 0) {
		//InvokeLoseEvent();
		_kingHP = 0;
	}
	if (_timeFramePerSec <= 0) {
		//InvokeWinEvent();
	}
}

void KingMoveManager::Draw() {
	if(!fallen)
			king.scaled(0.25).drawAt(_kingXPosition, Scene::Height() / 2);
	else false;
	//queen.scaled(0.25).drawAt((_timeFramePerSec * _scrollSpeedPerSec) + _kingXPosition + _kingPosOffset, Scene::Height() / 2);
	queenPos = Vec2((_timeFramePerSec * _scrollSpeedPerSec) + _kingXPosition + _kingPosOffset, Scene::Height() / 2);
	_gaugeBackImage.draw();
	_hpGaugebackImage.draw();
	RectF{ _gaugeBackImage.x + 10, _gaugeBackImage.y + 10, (_gaugeBackImage.w - 20) * (_timeFramePerSec / _kingMoveTimeSec), _gaugeBackImage.h - 20 }.draw(Palette::Blue);
	RectF{ _hpGaugebackImage.x + 2.5, _hpGaugebackImage.y + 2.5, (_hpGaugebackImage.w - 5) * ((double)_kingHP / (double)_kingMaxHP), _hpGaugebackImage.h - 5 }.draw(Palette::Green);
	if (_timeFramePerSec <= 0) {
		FontAsset(U"TitleFont")(U"Clear").drawAt(100, 100);
	}
}

char KingMoveManager::ReturnGameStatus() {
	if (_timeFramePerSec <= 0) {
		return 0b0100;
	}

	if (_kingHP <= 0) {
		return 0b0010;
	}

	return 0b0000;
}
