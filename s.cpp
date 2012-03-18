#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
class PG_flag
{
public:
	bool data[9];
	friend ostream& operator<<(ostream &os, const PG_flag& obj);
	PG_flag()
	{
		memset(data, 0, sizeof(data));

	}
	PG_flag(string q)
	{
		for (int i = 0; i < 9; i++)
		{
			data[i] = q[i] - '0';
		}
	}
	string show()
	{
		string r = "";
		for (int i = 0; i < 9; i++) r += (char)(data[i] + '0');
		return r;
	}
	int size()
	{
		int r = 0;
		for (int i = 0; i < 9; i++) if (data[i]) r++;
		return r;

	}
	bool &operator[](int q)
	{
		if (q < 0 || q > 8)
		{
			cout << "INDEX ERROR ! " << endl;
		}
		return data[q];
	}
	PG_flag operator|(PG_flag &in)
	{
		PG_flag r;
		for (int i = 0; i < 9; i++)
		{
			r.data[i] = data[i] | in.data[i]; 
		}
		return r;
	}
	PG_flag operator&(PG_flag &in)
	{
		PG_flag r;
		for (int i = 0; i < 9; i++)
		{
			r.data[i] = data[i] & in.data[i]; 
		}
		return r;
	}
	PG_flag operator-(PG_flag &in)
	{
		PG_flag r;
		for (int i = 0; i < 9; i++)
		{
			r.data[i] = in.data[i] ? false : data[i];
		}
		return r;
	}
	bool cut_by(PG_flag &in)
	{
		bool r = false;
		for (int i = 0; i < 9; i++)
		{
			if (in.data[i] && data[i])
			{
				data[i] = false;
				r = true;
			}
		}
		return r;
	}
	bool operator ==(PG_flag &in)
	{
		for (int i = 0; i < 9; i++)
		{
			if (data[i] != in.data[i]) return false;
		}
		return true;
	}

};
ostream& operator<<(ostream &os, const PG_flag &obj)
{

	
	for (int i = 0; i < 9; i++) os << obj.data[i];
	//os << "123";
	return os;
}
class PG_combination
{
public:

	int q[10];
	int data[10000][10];
	int max;
	int dfs(int a, int b, int d, int n)
	{
		q[d] = n;
		if (d == b - 1)
		{
			max++;
			for (int i = 0; i < b; i++)
				data[max][i] = q[i];
			return 0;
		}
		q[d] = n;
		for (int i = q[d] + 1; i <= a; i++)
		{
			dfs(a, b, d + 1, i);
		}

	}
	void show(int s)
	{
		cout << "MAX: " << max << endl;
		for (int i = 1; i <= max; i++)
		{
			for (int j = 0; j < s; j++)
			{
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
	void cal(int a, int b)
	{
		max = 0;
		for (int i = 1; i <= a; i++)
			dfs(a, b, 0, i);
	}
};
class PG_stat
{
public:
	int data[9][9];
	PG_flag flag[9][9];
	int debug_flag[9][9];
	void init()
	{
		memset(data, 0, sizeof(data));
		memset(flag, 1, sizeof(flag));
	}
	void read_input()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cin >> data[i][j];
			}
		}
	}
	void clear_debug_flag() {memset(debug_flag, 0, sizeof(debug_flag));}
	int left()
	{
		int r = 0;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (data[i][j] == 0) r++;
			}
		}
		return r;
	}

	void show()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		
	}
	void fill(int x, int y, int z)
	{
		data[y][x] = z;
		if (z == 0) return ;
		for (int i = 0; i < 9; i++) flag[y][x][i] = 0;
	}
	int count(int x, int y)
	{
		int r = 0;
		for (int i = 0; i < 9; i++)
			if (flag[y][x][i])r++;
		return r;
	}
	int test_and_return(int x, int y)
	{
		if (count(x, y) != 1) return -1;
		for (int i = 0; i < 9; i++)
		{
			if (flag[y][x][i])
			{
				return i + 1;
			}
		}
	}
	void count_debug()
	{
		cout << "/****************start of count_debug******************/" << endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << count(j, i) << " ";
			}
			cout << endl;
		}
		cout << "/****************end of count_debug******************/" << endl;
		
	}
	void flag_debug()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int z = 0; z < 9; z++)
				{
					if (flag[i][j][z])
						cout << z + 1 << ",";
				}
				cout << "/";
			}
			cout << endl;
		}
	}
	void flag_to_html(string fn)
	{
		ofstream fout(fn.data());
		fout << "<link href=\"sudoku.css\" type=\"text/css\" rel=\"Stylesheet\" />" << endl;
		fout << "<table border=\"1\">" << endl;
		for (int i = 0; i < 9; i++)
		{
			fout << "	<tr>" << endl;
			for (int j = 0; j < 9; j++)
			{
				int ti = i/3;
				int tj = j/3;
				bool background = false;
				if ( (tj == 0 || tj == 2) && (ti == 0 || ti == 2)) background = true;
				if ( ti == 1 && tj == 1) background = true;
				if (debug_flag[i][j])
					fout << "		<td class=\"debug_" << debug_flag[i][j] << "\">" << endl;
				else if (background)
					fout << "		<td class=\"background\">" << endl;
				else
					fout << "		<td>" << endl;
					
				if (data[i][j])
				{
					fout << "			<span style=\"font-size:2em\">" << data[i][j] << "</span>" << endl;
				}
				else
				{
					for (int k = 0; k < 9; k++)
					{
						fout << "&nbsp;";
						if (flag[i][j][k])fout << k+1;
						else fout << "&nbsp;";
						if (k % 3 == 2)fout << "<br/>";
					}
				}
				fout << endl;
				fout << "		</td>" << endl;
			}
			fout << "	</tr>" << endl;
		}
		fout << "</table>" << endl;
		fout.close();
	}
	void eliminate(int x, int y, int z)
	{
		if (z < 1 || z > 9){ cout << "error at eliminate" << endl; exit(1);}
		int sx = x - x % 3;
		int sy = y - y % 3;
		for (int i = sy; i < sy + 3; i++)
		{
			for (int j = sx; j < sx + 3; j++)
			{
				flag[i][j][z-1] = 0;
			}
		}
		for (int i = 0; i < 9; i++)
		{
			flag[y][i][z-1] = 0;
			flag[i][x][z-1] = 0;
		}
	}
	void fill_and_eliminate(int x, int y, int z)
	{
		data[y][x] = z;
		if (z == 0) return ;
		for (int i = 0; i < 9; i++) flag[y][x][i] = 0;
		eliminate(x, y, z);
	}

	void test()
	{
		init();
		read_input();
		show();
		while (1)
		{
			int a, b, c;
			cin >> a >> b >> c;
			eliminate(a, b, c);
			count_debug();
		}

	}
};
class PG_sudoku
{
public:
	PG_stat ori;
	PG_combination C_9_2, C_9_3;
	int result;
	void init()
	{
		ori.init();
		C_9_2.cal(9, 2);
		C_9_3.cal(9, 3);
	}
	void refresh(PG_stat &target)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				target.fill_and_eliminate(j, i, target.data[i][j]);
			}
		}
	}
	void init_input(PG_stat &target)
	{
		target.init();
		target.read_input();
		refresh(target);
	}
	void pick_grid(int x, int y, int in_x[9], int in_y[9])
	{
		int ptr = -1;
		for (int i = y * 3; i < y * 3 + 3; i++)
		{
			for (int j = x * 3; j < x * 3 + 3; j++)
			{
				ptr++;
				in_x[ptr] = j;
				in_y[ptr] = i;
			}
		}
	}
	void pick_grid(int at, int in_x[9], int in_y[9])
	{
		int x = at % 3;
		int y = at / 3;
		pick_grid(x, y, in_x, in_y);
	}

	void single_candidature(PG_stat &target)
	{
		
		bool key = 1;
		while (key)
		{
			key = 0;
			/* unique start */
			for (int i = 0; i < 9 && !key; i++)
			{
				for (int j = 0; j < 9 && !key; j++)
				{
					int tmp = target.test_and_return(j, i);
					if (tmp != -1)
					{
						//target.count_debug();
						cout << "[unique] find at " << j << " " << i << " " << tmp << endl;
						key = 1;
						target.fill_and_eliminate(j, i, tmp);
						//system("pause");
					}
				}
			}
			/* unique end */
			for (int k = 1; k <= 9 && !key; k++)
			{
				/* grid erase start */
				for (int i = 0; i < 3 && !key; i++) 
				{
				for (int j = 0; j < 3 && !key; j++)
				{
						int tmp = 0;
						int tx, ty;
						for (int ii = i * 3; ii < i * 3 + 3; ii++)
						{
							for (int jj = j * 3; jj < j * 3 + 3; jj++)
							{
								if (target.flag[ii][jj][k-1])
								{
									tmp++;
									tx = jj;
									ty = ii;
								}
							}
						}
						if (tmp == 1)
						{
							key = 1;
							cout << "[grid erase] find at " << tx << " " << ty << " " << k << endl;
							target.fill_and_eliminate(tx, ty, k);
						}
					
					}
				}
				/* grid erase end */

				/* row erase start */
				for (int i = 0; i < 9 && !key; i++)
				{
					int tmp = 0;
					int tx, ty;
					for (int j = 0; j < 9 && !key; j++)
					{
						if (target.flag[i][j][k-1])
						{
							tmp++;
							tx = j;
							ty = i;
						}
					}
					if (tmp == 1)
					{
						key = 1;
						cout << "[row erase] find at " << tx << " " << ty << " " << k << endl;
						target.fill_and_eliminate(tx, ty, k);
					}
				}
				/* row erase end */

				/* column erase start */
				for (int i = 0; i < 9 && !key; i++)
				{
					int tmp = 0;
					int tx, ty;
					for (int j = 0; j < 9 && !key; j++)
					{
						if (target.flag[j][i][k-1])
						{
							tmp++;
							tx = i;
							ty = j;
						}
					}
					if (tmp == 1)
					{
						key = 1;
						cout << "[column erase] find at " << tx << " " << ty << " " << k << endl;
						target.fill_and_eliminate(tx, ty, k);
					}
				}
				/* column erase end */
			}
		}

	}
	void locked_candidates_row_picker(int in_x, int in_y, int area_x[2][6], int area_y[2][6])
	{
		int sx = in_x - in_x % 3;
		int sy = in_y - in_y % 3;
		int x1 = in_x, x2 = in_x + 1, x3 = in_x + 2;
		int ptr;

		ptr = -1;
		for (int i = 0; i < 9; i++) // prepare area1
		{
			if (i != x1 && i != x2 && i != x3)
			{
				//cout << "set area1" << endl;
				ptr++;
				area_x[0][ptr] = i;
				area_y[0][ptr] = in_y;

			}
		}

		ptr = -1;
		for (int i = sy; i < sy+ 3; i++) //prepare area 2
		{
			if (i == in_y) continue;
			for (int j = sx; j < sx + 3; j++)
			{
				//cout << "set area2 " << endl;
				ptr++;
				area_x[1][ptr] = j;
				area_y[1][ptr] = i;
			}
		}
	}
	void locked_candidates_column_picker(int in_x, int in_y, int area_x[2][6], int area_y[2][6])
	{
		int sx = in_x - in_x % 3;
		int sy = in_y - in_y % 3;
		int y1 = in_y, y2 = in_y + 1, y3 = in_y + 2;
		int ptr;

		ptr = -1;
		for (int i = 0; i < 9; i++) // prepare area1
		{
			if (i != y1 && i != y2 && i != y3)
			{
				//cout << "set area1" << endl;
				ptr++;
				area_x[0][ptr] = in_x;
				area_y[0][ptr] = i;

			}
		}

		ptr = -1;
		for (int i = sy; i < sy+ 3; i++) //prepare area 2
		{
			
			for (int j = sx; j < sx + 3; j++)
			{
				if (j == in_x) continue;

				ptr++;
				area_x[1][ptr] = j;
				area_y[1][ptr] = i;
			}
		}
	}
	bool locked_candidates_unit(int in_x, int in_y, PG_stat &target, int area_x[2][6], int area_y[2][6], bool area_flag[2][9], string msg)
	{
		if (msg != "row" && msg != "column"){cout << "msg err @ locked_candidates_unit" << endl; system("pause");}
		int sx = in_x - in_x % 3;
		int sy = in_y - in_y % 3;
		int x1 = in_x, x2 = in_x + 1, x3 = in_x + 2;
		int y1 = in_y, y2 = in_y + 1, y3 = in_y + 2;
		bool flag = false;

		memset(area_flag, 0, sizeof(area_flag));
		target.clear_debug_flag();

		for (int i = 0; i < 9; i++) // find the union in area 1, 2 respectively
		{
			for (int j = 0; j < 6; j++)
			{
				int tx0 = area_x[0][j], ty0 = area_y[0][j];
				int tx1 = area_x[1][j], ty1 = area_y[1][j];
				target.debug_flag[ty0][tx0] = 1;
				target.debug_flag[ty1][tx1] = 2;
				area_flag[0][i] |= target.flag[ty0][tx0][i];
				area_flag[1][i] |= target.flag[ty1][tx1][i];
			}
		}
		//target.flag_to_html("locked2.html");
		for (int i = 0; i < 2; i ++) // area 1, 2 respectively
		{
			// let's assume a = area1, b = area2;
			int a = i, b = 1 - i;
			for (int j = 0; j < 9; j++) // check each number
			{
				if (area_flag[a][j] == false) // if j dosen't appear in area 1 , so should area 2.
				{
					if (msg == "row")
					{
						if (target.flag[in_y][x1][j] == false && 
							target.flag[in_y][x2][j] == false &&
							target.flag[in_y][x3][j] == false) continue;
					}
					if (msg == "column")
					{
						if (target.flag[y1][in_x][j] == false && 
							target.flag[y2][in_x][j] == false &&
							target.flag[y3][in_x][j] == false) continue;
					}
					cout << "area " << i << " / " << j << " is false" << endl;
					for (int k = 0; k < 6; k++) // for each point in area 2.
					{
						int tx = area_x[b][k], ty = area_y[b][k];

						if (target.flag[ty][tx][j]) 
						{
							// we find that a(area1) is false, but b(area2) is true.
							// fix it and print msg.
							target.debug_flag[ty][tx] = 3;
							target.flag_to_html("locked.html");
							target.flag[ty][tx][j] = false;
							cout << "[locked_candidates_" << msg << "] at point " << in_x << " " << in_y << endl;
							cout << "clear (" << tx << "," << ty << ")_" << j << endl;
							flag = true;
							system("pause");
						}
					}
				}
			}
		}
		return flag;
	}
	bool locked_candidates_main(int in_x, int in_y, PG_stat &target)
	{
		int sx = in_x - in_x % 3;
		int sy = in_y - in_y % 3;
		int x1 = in_x, x2 = in_x + 1, x3 = in_x + 2;
		int area_x[2][6], area_y[2][6];
		bool area_flag[2][9];
		int ptr;

		bool flag = false;
		
		locked_candidates_row_picker(in_x, in_y, area_x, area_y);
		flag |= locked_candidates_unit(in_x, in_y, target, area_x, area_y, area_flag, "row");
		if (flag) return true;
		locked_candidates_column_picker(in_x, in_y, area_x, area_y);
		flag |= locked_candidates_unit(in_x, in_y, target, area_x, area_y, area_flag, "column");
		return flag;
	}
	void locked_candidates(PG_stat &target)
	{
		target.flag_to_html("test.html");
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j +=3 )
			{
				if (locked_candidates_main(j, i, target)) return;
			}
		}
	}
	bool naked_pairs_unit(PG_stat &target, int in_x[9], int in_y[9])
	{
		for (int i = 1; i <= C_9_2.max; i++)
		{
			//choose 2 numbers by C(9,2)
			int a_x = in_x[C_9_2.data[i][0] - 1];
			int a_y = in_y[C_9_2.data[i][0] - 1];
			int b_x = in_x[C_9_2.data[i][1] - 1];
			int b_y = in_y[C_9_2.data[i][1] - 1];
			PG_flag &a = target.flag[a_y][a_x];
			PG_flag &b = target.flag[b_y][b_x];

			//count the available number size
			int ca = a.size();
			int cb = b.size();

			if (ca == 2 && cb == 2 && a == b)
			{
				cout << "detect at" << a_x << " " << a_y << " " << b_x << " " << b_y << endl;
				bool modified = false;
				for (int j = 0; j < 9; j++)
				{

					if (j == C_9_2.data[i][0]-1 || j == C_9_2.data[i][1]-1) continue;
					//cout << "before " << target.flag[ in_y[j] ][ in_x[j] ] << endl;
					modified |= target.flag[ in_y[j] ][ in_x[j] ].cut_by(a);
					//cout << "after " << target.flag[ in_y[j] ][ in_x[j] ] << endl;
				}
				if (modified) return true;	
			}
		}
		return false;
	}
	void naked_pairs(PG_stat &target)
	{
		int in_x[9], in_y[9];

		
		for (int i = 0; i < 9; i++)
		{
			/* pick row*/
			for (int j = 0; j < 9; j++)
			{
				in_y[j] = i;
				in_x[j] = j;
			}
			if (naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[naked pairs ] find pair at row " << i << endl;
				return;
			}

			/* pick column*/
			for (int j = 0; j < 9; j++)
			{
				in_y[j] = j;
				in_x[j] = i;
			}
			if (naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[naked pairs] find pair at column " << i << endl;
				return;
			}

			pick_grid(i, in_x, in_y);
			if (naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[naked pairs ] find pair at grid " << i << endl;
				return;
			}
		}
	}
	/*
	bool naked_triples_unit()
	{
		for (int i = 1; i <= C_9_3.max; i++)
		{
			//choose 3 numbers by C(9,3)
			bool *a = triple[C_9_3.data[i][0] - 1];
			bool *b = triple[C_9_3.data[i][1] - 1];
			bool *c = triple[C_9_3.data[i][2] - 1];

			//count the available number size
			int ca = 0; for (int j = 0; j < 9; j++) if(a[j]) ca++;
			int cb = 0; for (int j = 0; j < 9; j++) if(b[j]) cb++;
			int cc = 0; for (int j = 0; j < 9; j++) if(c[j]) cc++;


			if ((ca == 2 || ca == 3) && (cb == 2 || cb == 3) && (cc == 2 || cc == 3))
			{
				bool t[9];
				int tmp = 0;

				// find the union
				for (int j = 0; j < 9; j++)
				{ 
					t[j] = a[j] | b[j] | c[j];
					if (t[j]) tmp++;
				}

				//if the union size <=3
				if (tmp <= 3)
				{
					bool flag = 0;
					triple_final[0] = C_9_3.data[i][0] - 1;
					triple_final[1] = C_9_3.data[i][1] - 1;
					triple_final[2] = C_9_3.data[i][2] - 1;
					for (int j = 0; j < 9; j++) // for each number(1~9)
					{
						if (t[j]) // if this number is in the triples
						{
							for (int k = 0; k < 9; k++) 
							{
								if (triple[k] != a  &&  triple[k] != b  &&  triple[k] != c)
								{
									if (triple[k][j])
									{
										flag = 1;
										triple[k][j] = 0; // eliminate them !
										//cout << "eliminate number " << j << endl;
									}
								}

							}
						}
					}
					if (flag) return true;	
				}
			}
		}
		return false;
	}
	void naked_triples(PG_stat &target)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				triple[j] = target.flag[j][i];
			}
			if (naked_triples_unit())
			{
				cout << "[naked triples ] find triple at column " << i << endl;
				//cout << "find triple at " << triple_final[0] << " " 
				//<< triple_final[1] << " " << triple_final[2] << endl;
					     
			}
			for (int j = 0; j < 9; j++)
			{
				triple[j] = target.flag[i][j];
			}
			if (naked_triples_unit())
			{
				cout << "[naked triples] find triple at row " << i << endl;
				//cout << "find triple at " << triple_final[0] << " " 
				//<< triple_final[1] << " " << triple_final[2] << endl;
					     
			}
		}
	}
	*/
	void left_debug()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (ori.data[i][j] == 0)
				{
					cout << "left at " << i << " " << j << " has ";
					for (int k = 0; k < 9; k++)
					{
						if (ori.flag[i][j][k]) cout << k << " ";
					}
					cout << endl;
				}
			}
		}
	}
	void solve()
	{
		init_input(ori);
		int limit = 10;
		while (ori.left() > 0)
		{
			limit--;
			if (limit <= 0) break;
			cout << limit << " / left: " << ori.left() << endl; 
			single_candidature(ori);
			//refresh(ori);
			locked_candidates(ori);
			naked_pairs(ori);
			//naked_triples(ori);
		}
		ori.show();
		//left_debug();
		ori.count_debug();
	}
};
int main()
{
	PG_stat a;
	//a.test();
	PG_sudoku b;
	b.init();
	b.solve();

}
