#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//1 RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos{-1,0},	//UP
		Pos{0,-1},	//LEFT
		Pos{1,0},	//DOWN
		Pos{0,1},	//RIGHT
	};

	while (pos != dest)
	{
		//1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			//오른쪽 방향으로 90도 회전
			_dir = newDir;

			//앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		//2 현재 바라보는 방향을 기준으로 전진 할 수 있는지 확인.
		else if (CanGo(pos + front[_dir]))
		{
			//앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90회전
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	//스택으로 좌표를 추적 오른손법칙 개선
	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (!s.empty() && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	//목적지 도착
	if (!_path.empty())
		s.push(_path.back());

	vector <Pos>path;
	while (!s.empty())
	{
		path.push_back(s.top());
		s.pop();
	}
	std::reverse(path.begin(), path.end());
	_path = path;
}

void Player::Bfs()
{
	Pos pos = _pos;

	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos{-1,0},	//UP
		Pos{0,-1},	//LEFT
		Pos{1,0},	//DOWN
		Pos{0,1},	//RIGHT
	};

	int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size,false));
	
	map<Pos, Pos> parent;

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (!q.empty())
	{
		pos = q.front();
		q.pop();

		if (pos == dest)
			break;

		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];

			if (CanGo(nextPos) == false) continue;
			
			if (discovered[nextPos.y][nextPos.x]) continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}


	//TODO
	_path.clear();

	pos = dest;

	while (true)
	{
		_path.push_back(pos);
		
		//시작점은 자신이 곧 부모이다.
		if (pos == parent[pos]) break;

		pos = parent[pos];

	}

	_path.push_back(pos);
	std::reverse(_path.begin(), _path.end());
}
