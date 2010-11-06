#include "Strat.h"

void Strat::load(string dataFile,vector<Strat>& pop)
{

  // Magic number of population size
  pop.resize(12);
  // TODO Load genes
  ifstream in(dataFile.c_str());
  bool old=false;
  if(in.is_open())
  {
    int geneSize;
    in>>geneSize;
    if(geneSize != G_SIZE)
    {
      old=true;
    }
  }
  // If there was a database file
  if(in.is_open() && !old)
  {
    for(unsigned int i=0;i<pop.size();i++)
    {
      cout<<"Reading in "<<i<<endl;
      in>>pop[i].played;
      in>>pop[i].score;
      pop[i].gene.resize(G_SIZE);
      for(unsigned int g=0;g<G_SIZE;g++)
      {
        in>>pop[i].gene[g];
      }
    }
  }
  else
  {
    for(unsigned int i=0;i<pop.size();i++)
    {
      pop[i].played=false;
      pop[i].score=false;
      pop[i].gene.resize(G_SIZE);
      for(unsigned int g=0;g<G_SIZE;g++)
      {
        pop[i].gene[g]=rand()%10;
      }
    }
  }
  in.close();
}

void Strat::save(string dataFile,vector<Strat>& pop)
{
  ofstream out(dataFile.c_str());
  out<<(int)G_SIZE<<endl;
  // If there was a database file
  for(unsigned int i=0;i<pop.size();i++)
  {
    out<<pop[i].played<<" ";
    out<<pop[i].score<<" ";
    for(unsigned int g=0;g<G_SIZE;g++)
    {
      out<<pop[i].gene[g]<<" ";
    }
    out<<endl;
  }
}


