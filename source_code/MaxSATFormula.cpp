#include "MaxSATFormula.h"

void MaxSATFormula::build_ins(const char *ifilename, MaxSATFormula &maxsatformula)
{
  int linenum = 0;
  int &nclauses = maxsatformula.num_clauses;
  int &nvars = maxsatformula.num_vars;
  long long &top_clause_weight = maxsatformula.top_clause_weight;
  top_clause_weight = 0;
  nvars = 0;
  nclauses = 0;
  vector<SoftC> &sclause = maxsatformula.sclause;
  vector<HardC> &hclause = maxsatformula.hclause;
  ifstream ifile(ifilename);
  string line;
  getline(ifile, line);
  while (line[0] == '*')
    getline(ifile, line);

  if (line.substr(0, 4) == "min:")
  {
    stringstream ss;
    ss.str(line);
    ss.seekg(0, ios::beg);
    string tem_str;
    ss >> tem_str;
    ss >> tem_str;
    while (tem_str != ";")
    {
      // cout << tem_str << endl;
      SoftC tem_sc;
      bool if_neg = false;
      stringstream ss2;
      ss2.str(tem_str);
      ss2.seekg(0, ios::beg);
      ss2 >> tem_sc.weight;
      if (tem_sc.weight < 0)
      {
        if_neg = true;
        tem_sc.weight = -tem_sc.weight;
      }
      top_clause_weight += tem_sc.weight;
      ss >> tem_str;
      if (tem_str[0] != 'x')
      {
        cout << "1 wrong in reading obj: varibles name not begin with x" << endl;
        exit(0);
      }
      ss2.clear();
      ss2.str(tem_str.substr(1));
      ss2.seekg(0, ios::beg);

      int tem_var;
      ss2 >> tem_var;
      nvars = max(nvars, tem_var);
      Lit tem_lit;

      if (if_neg)
      {
        tem_lit.var = tem_var;
        tem_lit.weight = 1;
        tem_sc.clause.push_back(tem_lit);
      }
      else
      {
        tem_lit.var = -tem_var;
        tem_lit.weight = 1;
        tem_sc.clause.push_back(tem_lit);
      }
      tem_sc.degree = 1;
      sclause.push_back(tem_sc);
      ss >> tem_str;
    }
  }

  while (getline(ifile, line))
  {
    linenum++;
    if (line[0] == '*' || line[0] < 33)
      continue;

    stringstream ss;
    ss.str(line);
    ss.seekg(0, ios::beg);

    HardC tem_hc;
    tem_hc.degree = 0;

    // cout << "befor " << tem_hc.weight << endl;
    string tem_str;

    ss >> tem_str;
    while (tem_str != "=" && tem_str != ">=" && tem_str != "<=")
    {
      Lit tem_lit;
      bool if_neg = false;
      stringstream ss2;
      ss2.str(tem_str);
      ss2.seekg(0, ios::beg);

      ss2 >> tem_lit.weight;
      if (tem_lit.weight < 0)
      {
        if_neg = true;
        tem_lit.weight = -tem_lit.weight;
        tem_hc.degree += tem_lit.weight;
      }

      ss >> tem_str;
      if (tem_str[0] != 'x')
      {
        cout << "2 wrong in reading obj: varibles name not begin with x " << linenum << endl;
        exit(0);
      }
      ss2.clear();
      ss2.str(tem_str.substr(1));
      ss2.seekg(0, ios::beg);

      ss2 >> tem_lit.var;
      nvars = max(nvars, tem_lit.var);

      if (if_neg)
      {
        tem_lit.var = -tem_lit.var;
        tem_hc.clause.push_back(tem_lit);
      }
      else
        tem_hc.clause.push_back(tem_lit);

      ss >> tem_str;
    }

    if (tem_str == ">=")
    {
      ss >> tem_str;
      if (tem_str[tem_str.size() - 1] == ';')
      {
        tem_str = tem_str.substr(0, tem_str.size() - 1);
      }
      stringstream ss2;
      ss2.str(tem_str);
      int temdegree;
      ss2 >> temdegree;

      tem_hc.degree += temdegree;
      hclause.push_back(tem_hc);
    }
    else if (tem_str == "=")
    {
      ss >> tem_str;
      if (tem_str[tem_str.size() - 1] == ';')
      {
        tem_str = tem_str.substr(0, tem_str.size() - 1);
      }
      stringstream ss2;
      ss2.str(tem_str);
      int temdegree;
      ss2 >> temdegree;
      // cout << temdegree << endl;
      // cout << tem_hc.degree << endl;
      tem_hc.degree += temdegree;
      hclause.push_back(tem_hc);

      long long total_degree = 0;
      for (int i = 0; i < tem_hc.clause.size(); ++i)
      {
        total_degree += tem_hc.clause[i].weight;
        tem_hc.clause[i].var = -tem_hc.clause[i].var;
      }
      tem_hc.degree = total_degree -= tem_hc.degree;
      hclause.push_back(tem_hc);
    }
    else
    {
      ss >> tem_str;
      if (tem_str[tem_str.size() - 1] == ';')
      {
        tem_str = tem_str.substr(0, tem_str.size() - 1);
      }
      stringstream ss2;
      ss2.str(tem_str);
      int temdegree;
      ss2 >> temdegree;
      tem_hc.degree += temdegree;

      long long total_degree = 0;
      for (int i = 0; i < tem_hc.clause.size(); ++i)
      {
        total_degree += tem_hc.clause[i].weight;
        tem_hc.clause[i].var = -tem_hc.clause[i].var;
      }
      tem_hc.degree = total_degree -= tem_hc.degree;
      hclause.push_back(tem_hc);
    }

    // cout << "after " << tem_hc.weight << endl;
  }
}
