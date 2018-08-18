#ifndef _GAMESTATES_H_
#define _GAMESTATES_H_

enum State
{
	SPLASH,
	MENU,
	LOADING,
	GAME,
	WIN,
	PAUSE,
	OPTIONS
};

class GameStates
{
public:
	GameStates();
	~GameStates();
	GameStates(State startState);

	void ChangeState(State state);
	State GetState();

private:
	State m_state;
};

#endif // !_GAMESTATES_H_
