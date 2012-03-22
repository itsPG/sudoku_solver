/*
 * +----------------------------------------------------------------------+
 * | AI Sudoku Solver                                                     |
 * +----------------------------------------------------------------------+
 * | Copyright (c) 2012 PG @ SENSE Lab (http://www.eruru.tw)              |
 * +----------------------------------------------------------------------+
 * |           ^   ^                                                      |
 * |         _(;*ﾟーﾟ)＿_            ミカン箱は・・・                     |
 * |      ／ / つつ .／＼                                                 |
 * |    ／|￣￣￣￣|＼／                                                  |
 * |    |＿＿＿＿|／                                                      |
 * |                                                                      |
 * |            ^   ^                                                     |
 * |          _(;*ﾟーﾟ)＿_          ・・・・・・・・                      |
 * |       ／ / つつ .／＼                                                |
 * |    ／|￣￣￣￣|＼／                                                  |
 * |       |みかん  ..|／                                                 |
 * |       ￣￣￣￣                                                       |
 * +----------------------------------------------------------------------+
 * | Authors: PG Tsai <PG@miko.tw>                                        |
 * |                                                                      |
 * +----------------------------------------------------------------------+
 */


#include <iostream>
#include <fstream>
#include <sstream>
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
	bool cut_by(PG_flag &in, PG_flag &in2)
	{
		bool r = false;
		for (int i = 0; i < 9; i++)
		{
			if (in.data[i] && data[i])
			{
				data[i] = false;
				in2[i] = true;
				r = true;
			}
		}
		return r;
	}
	bool cut_by__inv(PG_flag &in, PG_flag &in2)
	{
		bool r = false;
		for (int i = 0; i < 9; i++)
		{
			if (in.data[i] == false && data[i])
			{
				data[i] = false;
				in2[i] = true;
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
	int get_num()
	{
		if (size() != 1)
		{
			cout << "!!! GET_NUM ERROR !!!" << endl;
			return -1;
		}
		else
		{
			for (int i = 0; i < 9; i++)
				if (data[i])
					return i;
		}
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
	PG_flag debug_flag_2[9][9];
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
	void clear_debug_flag()
	{
		memset(debug_flag, 0, sizeof(debug_flag));
		memset(debug_flag_2, 0, sizeof(debug_flag_2));
	}
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
				return i;
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
	string to_html()
	{
		ostringstream fout;
		
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
					fout << "			<span style=\"font-size:2em\">&nbsp;" << data[i][j] << "&nbsp;</span>" << endl;
				}
				else
				{
					for (int k = 0; k < 9; k++)
					{
						fout << "&nbsp;";

						if (debug_flag_2[i][j][k])
						{
							fout << "<span class=\"flag_debug_" << debug_flag_2[i][j][k] << "\">" << endl; 
						}

						if (flag[i][j][k] || debug_flag_2[i][j][k])
							fout << k+1;
						else
							fout << "&nbsp;";

						if (debug_flag_2[i][j][k])
								fout << "</span>" << endl;
						if (k % 3 == 2)fout << "<br/>";
					}
				}
				fout << endl;
				fout << "		</td>" << endl;
			}
			fout << "	</tr>" << endl;
		}
		fout << "</table>" << endl;
		//fout.close();
		return fout.str();
	}
	void eliminate(int x, int y, int z)
	{
		if (z < 0 || z > 8){ cout << "error at eliminate" << endl; exit(1);}
		int sx = x - x % 3;
		int sy = y - y % 3;
		for (int i = sy; i < sy + 3; i++)
		{
			for (int j = sx; j < sx + 3; j++)
			{
				flag[i][j][z] = 0;
			}
		}
		for (int i = 0; i < 9; i++)
		{
			flag[y][i][z] = 0;
			flag[i][x][z] = 0;
		}
	}
	void fill_and_eliminate(int x, int y, int z)
	{
		data[y][x] = z + 1;
		for (int i = 0; i < 9; i++) flag[y][x][i] = 0;
		eliminate(x, y, z);
	}
};

class PG_html
{
public:
	ofstream fout;
	int count;
	PG_html(string fn)
	{
		count = 0;
		fout.open(fn.data());
		fout << "<link href=\"sudoku.css\" type=\"text/css\" rel=\"Stylesheet\" />" << endl;
	}
	void add_stat(PG_stat &target, string msg)
	{
		count++;
		fout << "<div id=\"sudoku_" << count << "\">" << endl;
		fout << "<h2>" << msg << "</h2>" << endl;
		fout << target.to_html() << endl;
		fout << "</div>" << endl;
	}
	void add_msg(string msg)
	{
		fout << "<h3>" << msg << "</h3>" << endl;
	}
};
PG_html HTML("PG.html");
class PG_coordinate
{
public:
	int x, y;
	PG_coordinate(){ x = -1; y = -1;}
	bool chk()
	{
		return x > 0 && x < 9 && y > 0 && y < 9;
	}

};
class PG_sudoku
{
public:
	PG_stat ori;
	PG_combination C_9_2, C_9_3;
	int result;
	int field_x[3][9][9], field_y[3][9][9];
	static const int MODE_row = 0, MODE_column = 1, MODE_grid = 2;

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
	void init()
	{
		ori.init();
		C_9_2.cal(9, 2);
		C_9_3.cal(9, 3);
		int in_x[9], in_y[9];
		PG_stat d;
		for (int i = 0; i < 9; i++)
		{
			d.clear_debug_flag();
			pick_grid(i, in_x, in_y);
			for (int j = 0; j < 9; j++)
			{
				field_x[0][i][j] = j;
				field_y[0][i][j] = i; 
				field_x[1][i][j] = i;
				field_y[1][i][j] = j; 
				field_x[2][i][j] = in_x[j];
				field_y[2][i][j] = in_y[j];
				d.debug_flag[i][j] = 1;
				d.debug_flag[j][i] = 2;
				d.debug_flag[ in_y[j] ][ in_x[j] ] = 3;
			}
			//HTML.add_stat(d, "init");
		}
	}
	void refresh(PG_stat &target)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (target.data[i][j]) target.fill_and_eliminate(j, i, target.data[i][j] - 1);
			}
		}
	}
	void init_input(PG_stat &target)
	{
		target.init();
		target.read_input();
		refresh(target);
	}
	int BSC_count_area_empty_size(PG_stat &target, int mode, int at)
	{
		int r = 0;
		for (int i = 0; i < 9; i++)
		{
			int tx = field_x[mode][at][i];
			int ty = field_y[mode][at][i];
			if (target.data[ty][tx] == 0) r++;
		}
		return r;
	}
	bool BSC_look_for_number(PG_stat &target, int mode, int at, int q, int from, int &r_x, int &r_y)
	// mode[0~2]: row column grid, at:target area, q:query, from:for, r_x+r_y: result 
	{
		r_x = -1; 
		r_y = -1;
		for (int i = from; i < 9; i++)
		{
			int tx = field_x[mode][at][i];
			int ty = field_y[mode][at][i];
			if (target.data[ty][tx] == q)
			{
				r_x = tx;
				r_y = ty;
				return true;
			}
		}
		return false;
	}
	bool BSC_look_for_number(PG_stat &target, int mode, int at, int q, int &r_x, int &r_y)
	{
		return BSC_look_for_number(target, mode, at, q, 0, r_x, r_y);
	}
	int BSC_get_grid(int x, int y)
	{
		int a = x / 3;
		int b = y / 3;
		return b * 3 + a;
	}
	bool basic_tradidional_1_left(PG_stat &target)
	{
		bool flag = false;
		int r_x, r_y;
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 9; i++)
			{
				int s = BSC_count_area_empty_size(target, k, i);
				if (s == 1)
				{
					target.clear_debug_flag();
					int tx, ty, final;
					PG_flag tmp;
					BSC_look_for_number(target, k, i, 0, r_x, r_y);
					for (int j = 0; j < 9; j++)
					{
						tx = field_x[k][i][j];
						ty = field_y[k][i][j];

						int tmp2 = target.data[ty][tx] - 1;
						if (tmp2 == -1) continue;
						else tmp[ tmp2 ] = true;
					}
					for (int j = 0; j < 9; j++)
					{
						if (tmp[j] == false)
						{
							final = j;
							break;
						} 
					}
					target.debug_flag[r_y][r_x] = 1;
					target.fill_and_eliminate(r_x, r_y, final);
					HTML.add_stat(target, "basic_1_left");
				}
			}
		}
	}
	bool basic_n_left(PG_stat &target, int n)
	{
		int r_x, r_y;
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 9; i++)
			{
				int s = BSC_count_area_empty_size(target, k, i);
				if (s <= n)
				{
					target.clear_debug_flag();
					int tx, ty, final;
					PG_flag tmp;
					if (BSC_look_for_number(target, k, i, 0, r_x, r_y))
					{
						if (target.flag[r_y][r_x].size() == 1)
						{
							int final = target.flag[r_y][r_x].get_num();
							target.fill_and_eliminate(r_x, r_y, final);
							target.debug_flag[r_y][r_x] = 2;
							ostringstream sout;
							sout << "basic_n_left , using " << s << endl;
							HTML.add_stat(target, sout.str());
							return true;
						}
					}
					
				}
			}
		}
	}
	bool basic_grid_erase_unit(PG_stat &target, int n)
	{
		bool table[9][9] = {0};
		int cnt[3][3] = {0};
		bool flag = false;
		target.clear_debug_flag();
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (target.data[i][j] == n + 1)
				{
					for (int k = 0; k < 9; k++)
					{
						table[i][k] = true;
						table[k][j] = true;
						target.debug_flag[i][k] = 3;
						target.debug_flag[k][j] = 3;
					}
					target.debug_flag[i][j] = 1;
				}
			}
		}

		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cnt[i/3][j/3] += table[i][j];
			}
		}
		

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (table[i][j] == false && cnt[i/3][j/3] == 8 && target.data[i][j] == 0 && target.flag[i][j][n])
				{
					target.debug_flag[i][j] = 2;
					target.fill_and_eliminate(j, i, n);
					flag = true;
				}
			}
		}
		return flag;
	}
	bool basic_grid_erase(PG_stat &target)
	{
		bool flag = false;
		for (int i = 0; i < 9; i++)
		{
			bool tmp = basic_grid_erase_unit(target, i);
			if (tmp)
			{
				flag = true;
				HTML.add_stat(target, "basic_grid_erase");
			}
		}
		return flag;
	}
	void single_candidature(PG_stat &target)
	{
		
		bool key = true;
		while (key)
		{
			key = false;
			/* unique start */
			for (int i = 0; i < 9 && !key; i++)
			{
				for (int j = 0; j < 9 && !key; j++)
				{
					int tmp = target.test_and_return(j, i);
					if (tmp != -1)
					{
						cout << "[unique] find at " << j << " " << i << " " << tmp << endl;
						key = true;
						target.fill_and_eliminate(j, i, tmp);
						target.clear_debug_flag();
						target.debug_flag[i][j] = 2;
						HTML.add_stat(target, "single condidate");

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
							target.fill_and_eliminate(tx, ty, k - 1);
							target.clear_debug_flag();
							target.debug_flag[ty][tx] = 2;
							HTML.add_stat(target, "grid hidden single condidate");
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
						target.fill_and_eliminate(tx, ty, k-1);
						target.clear_debug_flag();
						target.debug_flag[ty][tx] = 2;
						HTML.add_stat(target, "row hidden single condidate");
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
						target.fill_and_eliminate(tx, ty, k-1);
						target.clear_debug_flag();
						target.debug_flag[ty][tx] = 2;
						HTML.add_stat(target, "column hidden single condidate");
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
		int x1 = sx, x2 = sx + 1, x3 = sx + 2;
		int ptr;

		ptr = -1;
		for (int i = 0; i < 9; i++) // prepare area1
		{
			if (i != x1 && i != x2 && i != x3)
			{
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
		int y1 = sy, y2 = sy + 1, y3 = sy + 2;
		int ptr;

		ptr = -1;
		for (int i = 0; i < 9; i++) // prepare area1
		{
			if (i != y1 && i != y2 && i != y3)
			{
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
		if (msg != "row" && msg != "column"){cout << "msg err @ locked_candidates_unit" << endl; exit(1);}
		int sx = in_x - in_x % 3;
		int sy = in_y - in_y % 3;
		int x1 = in_x, x2 = in_x + 1, x3 = in_x + 2;
		int y1 = in_y, y2 = in_y + 1, y3 = in_y + 2;
		bool flag = false;

		//memset(area_flag, 0, sizeof(area_flag)); (god damm it...............)
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 9; j++)
				area_flag[i][j] = false;
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
				target.debug_flag[ty0][tx0] = 1;
				target.debug_flag[ty1][tx1] = 2;
			}
		}
		

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

					for (int k = 0; k < 6; k++) // for each point in area 2.
					{
						int tx = area_x[b][k], ty = area_y[b][k];

						if (target.flag[ty][tx][j]) 
						{
							// we find that a(area1) is false, but b(area2) is true.
							// fix it and print msg.

							target.debug_flag[ty][tx] = 3;
							target.debug_flag_2[ty][tx][j] = 1;
							
							target.flag[ty][tx][j] = false;
							cout << "[locked_candidates_" << msg << "] at point " << in_x << " " << in_y << endl;
							cout << "clear (" << tx << "," << ty << ")_" << j << endl;
							flag = true;
						}
					}
				}
			}
			if (flag) HTML.add_stat(target, "locked candidates");
		}
		
		return flag;
	}
	bool locked_candidates_main(int in_x, int in_y, PG_stat &target, int mode) // mode1:row mode2:column
	{
		int sx = in_x - in_x % 3;
		int sy = in_y - in_y % 3;
		int x1 = in_x, x2 = in_x + 1, x3 = in_x + 2;
		int area_x[2][6], area_y[2][6];
		bool area_flag[2][9];
		int ptr;

		bool flag = false;
		
		if (mode == 1)
		{
			locked_candidates_row_picker(in_x, in_y, area_x, area_y);
			flag |= locked_candidates_unit(in_x, in_y, target, area_x, area_y, area_flag, "row");
		}
		else if (mode == 2)
		{
			locked_candidates_column_picker(in_x, in_y, area_x, area_y);
			flag |= locked_candidates_unit(in_x, in_y, target, area_x, area_y, area_flag, "column");
		}
		else
		{
			cout << "!!!ERROR!!! at locked_candidates_main" << endl;
			exit(1);
		}
		return flag;
	}

	bool locked_candidates(PG_stat &target)
	{
		for (int i = 0; i < 9; i += 1)
		{
			for (int j = 0; j < 9; j += 3 )
			{
				target.clear_debug_flag();
				if (locked_candidates_main(j, i, target, 1)) return true;
			}
		}
		for (int i = 0; i < 9; i += 3)
		{
			for (int j = 0; j < 9; j += 1 )
			{
				target.clear_debug_flag();
				if (locked_candidates_main(j, i, target, 2)) return true;
			}
		}
		return false;
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
				bool modified = false;
				target.clear_debug_flag();
				target.debug_flag[a_y][a_x] = 1;
				target.debug_flag[b_y][b_x] = 1;
				PG_stat tmp = target;
				for (int j = 0; j < 9; j++)
				{
					if (j == C_9_2.data[i][0]-1 || j == C_9_2.data[i][1]-1) continue;
					bool tmp_flag = target.flag[ in_y[j] ][ in_x[j] ].cut_by(a, target.debug_flag_2[ in_y[j] ][ in_x[j] ]);
					modified |= tmp_flag;
				}
				if (modified)
				{
					HTML.add_stat(target, "naked_pairs");
					return true;	
				} 
			}
		}
		return false;
	}
	bool hidden_naked_pairs_unit(PG_stat &target, int in_x[9], int in_y[9])
	{
		target.clear_debug_flag();
		PG_stat target2 = target;
		int count[9] = {0};
		for (int i = 0; i < 9; i++) // for each in_?
		{
			for (int j = 0; j < 9; j++) // for each number
			{
				if (target2.flag[ in_y[i] ][ in_x[i] ][j])
					count[j]++;
			}
		}
		for (int i = 0; i < 9; i++) //for each number
		{
			if (count[i] > 2)
			{
				for (int j = 0; j < 9; j++) // for each in_?
				{
					target2.flag[ in_y[j] ][ in_x[j] ][i] = false;
					target2.debug_flag_2[ in_y[j] ][ in_x[j] ][i] = 1;
				}
			}
		}

		for (int i = 1; i <= C_9_2.max; i++)
		{
			//choose 2 numbers by C(9,2)
			int a_x = in_x[C_9_2.data[i][0] - 1];
			int a_y = in_y[C_9_2.data[i][0] - 1];
			int b_x = in_x[C_9_2.data[i][1] - 1];
			int b_y = in_y[C_9_2.data[i][1] - 1];
			PG_flag &a = target2.flag[a_y][a_x];
			PG_flag &b = target2.flag[b_y][b_x];

			//count the available number size
			int ca = a.size();
			int cb = b.size();

			if (ca == 2 && cb == 2 && a == b)
			{
				target.clear_debug_flag();
				target.debug_flag[a_y][a_x] = 1;
				target.debug_flag[b_y][b_x] = 1;
				bool modified = false;
				PG_stat tmp = target;
				{
					bool tmp_flag = target.flag[ a_y ][ a_x ].cut_by__inv(a, target.debug_flag_2[ a_y ][ a_x ]);
					modified |= tmp_flag;
					tmp_flag = target.flag[ b_y ][ b_x ].cut_by__inv(a, target.debug_flag_2[ b_y ][ b_x ]);
					modified |= tmp_flag;
				}
				if (modified)
				{
					HTML.add_stat(target, "hidden_naked_pairs");
					return true;	
				} 
			}
		}
		return false;
	}
	bool naked_pairs(PG_stat &target)
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
				return true;
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
				return true;
			}
			/* pick grid*/
			pick_grid(i, in_x, in_y);
			if (naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[naked pairs ] find pair at grid " << i << endl;
				return true;
			}
		}
		return false;

	}
	bool hidden_naked_pairs(PG_stat &target)
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
			if (hidden_naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[hidden naked pairs ] find pair at row " << i << endl;
				return true;
			}
			/* pick column*/
			for (int j = 0; j < 9; j++)
			{
				in_y[j] = j;
				in_x[j] = i;
			}
			if (hidden_naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[hidden naked pairs] find pair at column " << i << endl;
				return true;
			}
			/* pick grid*/
			pick_grid(i, in_x, in_y);
			if (hidden_naked_pairs_unit(target, in_x, in_y))
			{
				cout << "[hidden naked pairs ] find pair at grid " << i << endl;
				return true;
			}
		}
		return false;
		
	}
	bool naked_triples_unit(PG_stat &target, int in_x[9], int in_y[9])
	{
		for (int i = 1; i <= C_9_3.max; i++)
		{
			//choose 3 numbers by C(9,3)
			int a_x = in_x[C_9_3.data[i][0] - 1];
			int a_y = in_y[C_9_3.data[i][0] - 1];
			int b_x = in_x[C_9_3.data[i][1] - 1];
			int b_y = in_y[C_9_3.data[i][1] - 1];
			int c_x = in_x[C_9_3.data[i][2] - 1];
			int c_y = in_y[C_9_3.data[i][2] - 1];
			if (target.data[a_y][a_x] != 0) continue;
			if (target.data[b_y][b_x] != 0) continue;
			if (target.data[c_y][c_x] != 0) continue;
			PG_flag &a = target.flag[a_y][a_x];
			PG_flag &b = target.flag[b_y][b_x];
			PG_flag &c = target.flag[c_y][c_x];
			PG_flag d = a | b | c ;
			//count the available number size
			int ca = a.size();
			int cb = b.size();
			int cc = c.size();
			int cd = d.size();

			if (cd <= 3)
			{
				target.debug_flag[a_y][a_x] = 2;
				target.debug_flag[b_y][b_x] = 2;
				target.debug_flag[c_y][c_x] = 2;
				bool modified = false;
				for (int j = 0; j < 9; j++)
				{
					int tx = in_x[j], ty = in_y[j];
					if (tx == a_x && ty == a_y) continue;
					if (tx == b_x && ty == b_y) continue;
					if (tx == c_x && ty == c_y) continue;
					bool flag_tmp = target.flag[ty][tx].cut_by(d, target.debug_flag_2[ty][tx]);
					modified |= flag_tmp;
					if (flag_tmp)
					{
						HTML.add_stat(target, "naked_triples");
					}
				}
			}
		}
		return false;
	}
	bool hidden_naked_triples_unit(PG_stat &target, int in_x[9], int in_y[9])
	{
		int count[9] = {0};
		for (int i = 0; i < 9; i++) // for each in_?
		{
			for (int j = 0; j < 9; j++) // for each number
			{
				if (target.flag[ in_y[i] ][ in_x[i] ][j])
					count[j]++;
			}
		}
		for (int k = 1; k <= C_9_3.max; k++)
		{
			int flag_continue = false;
			int chosen[3];
			for (int i = 0; i < 3; i++) 
			{
				chosen[i] = C_9_3.data[k][i] - 1;
				if (count[ chosen[i] ] > 3) flag_continue = true;
				if (count[ chosen[i] ] == 0) flag_continue = true;
			}
			if (flag_continue) continue;
			
			PG_flag place;  
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					PG_flag &t = target.flag[ in_y[j] ][ in_x[j] ];
					if (t[ chosen[i] ]) place[j] = true; 
				}
			}

			if (place.size() <= 3) // if those numbers appears at less than 3 place
			{

				target.clear_debug_flag();
				for (int i = 0; i < 9 ;i++) target.debug_flag[ in_y[i] ][ in_x[i] ] = 1;
				//PG_stat target2 = target;
				PG_flag tmp; // tmp is used for cut
				tmp[ chosen[0] ] = true;
				tmp[ chosen[1] ] = true;
				tmp[ chosen[2] ] = true;
				bool modified = false;
				for (int i = 0; i < 9 ;i++) // for each place 
				{
					if (place[i]) // means this place need to be cut by hidden triples
					{
						int tx = in_x[i];
						int ty = in_y[i];
						modified |= target.flag[ty][tx].cut_by__inv(tmp, target.debug_flag_2[ty][tx]);
						target.debug_flag[ty][tx] = 2;
					}
				}
				if (modified)
				{
					HTML.add_stat(target, "hidden triples");
				}

			}
		}
	}
	void naked_triples_row_picker(PG_stat &target, int in_x[9], int in_y[9], int row)
	{
		target.clear_debug_flag();
		for (int j = 0; j < 9; j++)
		{
			in_x[j] = j;
			in_y[j] = row;
			target.debug_flag[row][j] = 1;
		}
	}
	void naked_triples_column_picker(PG_stat &target, int in_x[9], int in_y[9], int column)
	{
		target.clear_debug_flag();
		for (int j = 0; j < 9; j++)
		{
			in_x[j] = column;
			in_y[j] = j;
			target.debug_flag[j][column] = 1;
		}
	}
	void naked_triples_grid_picker(PG_stat &target, int in_x[9], int in_y[9], int grid) // grid: 0~8
	
	{
		target.clear_debug_flag();
		int sx = (grid % 3) * 3;
		int sy = (grid / 3) * 3;
		int ptr = -1;
		for (int i = sy; i < sy + 3; i++)
		{
			for (int j = sx; j < sx + 3; j++)
			{
				ptr++;
				in_x[ptr] = j;
				in_y[ptr] = i;
				target.debug_flag[i][j] = 1;
			}
		}
	}
	bool naked_triples_main(PG_stat &target, int mode) // mode1: normal , mode2: hidden
	{
		int ptr, in_x[9], in_y[9];
		for (int k = 0; k < 3; k++)
		{

			for (int i = 0; i < 9; i++)
			{
				if      (k == 0) naked_triples_row_picker(target, in_x, in_y, i);
				else if (k == 1) naked_triples_column_picker(target, in_x, in_y, i);
				else if (k == 2) naked_triples_grid_picker(target, in_x, in_y, i);
				else             cout << "!!!ERROR!! at naked_triples_main" << endl;

				bool tmp;

				if (mode == 1)
					tmp = naked_triples_unit(target, in_x, in_y);
				else if (mode == 2)
					tmp = hidden_naked_triples_unit(target, in_x, in_y);
				else
					cout << "!!!ERROR!!! at naked_triples_main" << endl;

				if (tmp)
				{
					string s_tmp = "[triples] ";
					if (mode == 1) s_tmp += "normal ";
					if (mode == 2) s_tmp += "hidden ";
					if (k == 0) s_tmp += "row ";
					if (k == 1) s_tmp += "column ";
					if (k == 2) s_tmp += "grid ";
					HTML.add_stat(target, s_tmp);
					cout << "[triples]" << endl;
					return true;
				}
			}
		}
		return false;
	}
	bool naked_triples(PG_stat &target)
	{
		return naked_triples_main(target, 1);
	}
	bool hidden_naked_triples(PG_stat &target)
	{
		return naked_triples_main(target, 2);
	}
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
		HTML.add_stat(ori, "ORIGIN");
		int limit = 10;
		while (ori.left() > 0)
		{
			limit--;
			if (limit <= 0) break;
			cout << limit << " / left: " << ori.left() << endl; 

			if (basic_n_left(ori, 1)) { limit++; continue;}
			//if (basic_n_left(ori, 2)) { limit++; continue;}
			//if (basic_n_left(ori, 3)) { limit++; continue;}
			if (basic_grid_erase(ori)) { limit++; continue;}
			single_candidature(ori);

			if (locked_candidates(ori)) { limit++; continue;}

			if (naked_pairs(ori)) { limit++; continue;}
			if (hidden_naked_pairs(ori)) { limit++; continue;}

			if (naked_triples(ori)) { limit++; continue;}
			if (hidden_naked_triples(ori)) { limit++; continue;}

		}
		ori.show();
		//left_debug();
		ori.count_debug();
		HTML.add_stat(ori, "FINAL");
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
