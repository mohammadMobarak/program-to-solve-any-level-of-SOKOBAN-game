//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;
#define ll long long
// empty ->>               .
// obstacle ->>            #
// box ->>                 B
// charachter ->>          C
// spot for a box - >>     O
// charachter on spot ->>  *
// box on sopt ->>         !


ll z = 0;
void print(vector<vector<char>>vec)
{
	//cout<<"the game now is : "<<endl;
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}
bool valid(vector<vector<char>>v, int rows, int columns)
{
	bool ok = true;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (v[i][j] == 'B')
			{
				ok = false;
				break;
			}
		}
		if (ok == false)
		{
			break;
		}
	}
	return ok;
}
vector<char> new_spots(char c1, char c2, char c3)
{
	if (c1 != 'C' && c1 != '*')
	{
		for (int i = 0; i < 1000000000; i++)
		{
			cout << "A";
		}
		cout << endl;
	}
	vector<char>v;
	char t1, t2, t3;
	bool next_is_box = false, after_next_is_blocked = false;
	if (c2 == 'B' || c2 == '!')
	{
		next_is_box = true;
	}
	if (c3 == 'B' || c3 == '!' || c3 == '#')
	{
		after_next_is_blocked = true;
	}
	if (next_is_box && after_next_is_blocked)
	{
		return v;
	}
	if (c2 == 'B' || c2 == '!')
	{
		if (c3 == '.' || c3 == 'O')
		{
			if (c3 == '.')
			{
				t3 = 'B';
			}
			else
			{
				t3 = '!';
			}
		}
		if (c2 == 'B')
		{
			t2 = 'C';
		}
		else
		{
			t2 = '*';
		}
		if (c1 == 'C')
		{
			t1 = '.';
		}
		else
		{
			t1 = 'O';
		}
	}
	else if (c2 == '.')
	{
		t2 = 'C';
		t3 = c3;
		if (c1 == 'C')
		{
			t1 = '.';
		}
		else
		{
			t1 = 'O';
		}
	}
	else if (c2 == 'O')
	{
		t2 = '*';
		t3 = c3;
		if (c1 == 'C')
		{
			t1 = '.';
		}
		else
		{
			t1 = 'O';
		}
	}
	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);
	return v;
}

void bfs(vector<vector<char>>vec, int& rows, int& columns, map<vector<vector<char>>, bool >& mp, vector<char>& ans)
{
	queue<vector<vector<char>>>q;
	q.push(vec);
	while (q.size() > 0)
	{
		ll current_size = q.front()[rows].size();
		if (current_size > z)
		{
			z = current_size;
			cout << "I have searched for " << z << " steps !" << endl;
		}
		bool bad = false;
		vector<vector<char>>tmp = q.front();
		q.pop();
		if (valid(tmp, rows, columns))
		{
			for (int i = 0; i < tmp[rows].size(); i++)
			{
				ans.push_back(tmp[rows][i]);
			}
			break;
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (tmp[i][j] == 'B')
				{
					int counter = 0;
					if (tmp[i - 1][j] == '#' && tmp[i][j - 1] == '#')
					{
						counter += 1;
					}
					if (tmp[i + 1][j] == '#' && tmp[i][j + 1] == '#')
					{
						counter += 1;
					}
					if (tmp[i][j + 1] == '#' && tmp[i - 1][j] == '#')
					{
						counter += 1;
					}
					if (tmp[i][j - 1] == '#' && tmp[i + 1][j] == '#')
					{
						counter += 1;
					}
					if (counter > 1)
					{
						bad = true;
						break;
					}
				}
			}
			if (bad)
			{
				break;
			}
		}
		if (bad)
		{
			continue;
		}
		vector<vector<char>>vec_right = tmp;
		vector<vector<char>>vec_down = tmp;
		vector<vector<char>>vec_left = tmp;
		vector<vector<char>>vec_up = tmp;
		int x = 0, y = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (tmp[i][j] == 'C' || tmp[i][j] == '*')
				{
					x = i;
					y = j;
					break;
				}
			}
		}
		// right
		if (vec[x][y + 1] != '#')// if the place I am going to is not a wall
		{
			vector<char>new_cells = new_spots(tmp[x][y], tmp[x][y + 1], tmp[x][y + 2]);
			if (new_cells.size() > 0)
			{
				vec_right[x][y] = new_cells[0];
				vec_right[x][y + 1] = new_cells[1];
				vec_right[x][y + 2] = new_cells[2];
				vec_right[rows].push_back('R');
				vector<vector<char>>a1 = vec_right;
				a1.pop_back();
				if (mp[a1] == false)
				{
					mp[a1] = true;
					q.push(vec_right);
				}
			}
		}
		// down 
		if (vec[x + 1][y] != '#')// if the place I am going to is not a wall
		{
			vector<char>new_cells = new_spots(tmp[x][y], tmp[x + 1][y], tmp[x + 2][y]);
			if (new_cells.size() > 0)
			{
				vec_down[x][y] = new_cells[0];
				vec_down[x + 1][y] = new_cells[1];
				vec_down[x + 2][y] = new_cells[2];
				vec_down[rows].push_back('D');
				vector<vector<char>>a2 = vec_down;
				a2.pop_back();
				if (mp[a2] == false)
				{
					mp[a2] = true;
					q.push(vec_down);

				}
			}
		}
		// left
		if (vec[x][y - 1] != '#')// if the place I am going to is not a wall
		{
			vector<char>new_cells = new_spots(tmp[x][y], tmp[x][y - 1], tmp[x][y - 2]);
			if (new_cells.size() > 0)
			{
				vec_left[x][y] = new_cells[0];
				vec_left[x][y - 1] = new_cells[1];
				vec_left[x][y - 2] = new_cells[2];
				vec_left[rows].push_back('L');
				vector<vector<char>>a3 = vec_left;
				a3.pop_back();
				if (mp[a3] == false)
				{
					mp[a3] = true;
					q.push(vec_left);
				}
			}
		}
		//up
		if (vec[x - 1][y] != '#')// if the place I am going to is not a wall
		{
			vector<char>new_cells = new_spots(tmp[x][y], tmp[x - 1][y], tmp[x - 2][y]);
			if (new_cells.size() > 0)
			{
				vec_up[x][y] = new_cells[0];
				vec_up[x - 1][y] = new_cells[1];
				vec_up[x - 2][y] = new_cells[2];
				vec_up[rows].push_back('U');
				vector<vector<char>>a4 = vec_up;
				a4.pop_back();
				if (mp[a4] == false)
				{
					mp[a4] = true;
					q.push(vec_up);
				}
			}
		}
	}
}
int main()
{


	cout << "enter the number of rows : ";
	int rows;
	cin >> rows;
	cout << "enter the number of columns : ";
	int columns;
	cin >> columns;
	vector<vector<char>>vec(rows + 1);
	map<vector<vector<char>>, bool >mp;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char cell;
			cin >> cell;
			vec[i].push_back(cell);
		}
	}

	vector<char>ans;
	vector<vector<char>>test_vec(rows);

	bfs(vec, rows, columns, mp, ans);
	cout << " the directions to win this level are : " << endl;
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
	return 0;
}