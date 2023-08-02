#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> 
#include <cmath>
#include<iomanip>

using namespace std;

class recipe {
public:
	recipe(int a, string t, string b, string c, string d, string e, string f, string ch);
	int get_id() { return id; }
	string get_title() { return title; };
	string get_vegetarian() { return vegetarian; };
	string get_ingredients() { return ingredients; };
	string get_min_to_ready() { return min_to_ready; };
	string get_tags() { return tags; };
	string get_img_adr() { return img_adr; }
	void set_score(float a);
	string get_chef() { return chef; }
	vector<float> get_score() { return score; }
private:
	int id;
	string title;
	string vegetarian;
	string ingredients;
	string min_to_ready;
	string tags;
	string img_adr;
	vector<float> score;
	string chef;
};


class shelf {
public:
	shelf(string a, int b, string c) { name = a; id = b; user = c; }
	string get_user() { return user; }
	void print();
	int get_id() { return id; }
	void get_recipe(recipe recipeee) { recipee.push_back(recipeee); }
	void erase(int id);
	vector<recipe>give_recipe() { return recipee; }
	void print_recipe();
	string get_name() { return name; }
private:
	string name;
	int id;
	string user;
	vector<recipe>recipee;
};


class User {
public:
	User(string b, string c,int id) {
		username = b;
		password = c;
		ID = id;
	}
	virtual string get_type() = 0;
	string get_username() { return username; }
	string get_password() { return password; }
	int get_id() { return ID; }

protected:
	string username;
	string password;
	int ID;
};


class normal_user :public User {
public:
	normal_user(string b, string c,int id);
	string get_type() { return type; }
private:
	string type = "user";
	vector<shelf>shelff;
	int rate_limits = 0;
	vector<int>rated_recipes;
};


class chef :public User {
public:
	chef(string b, string c,int id);
	vector<recipe> get_recipe() { return recipee; }
	string get_type() { return type; }

private:
	vector<recipe>recipee;
	vector<float> score;
	string type = "chef";
};


class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  LoginHandler(vector<User*>* user) {users = user;}
  Response *callback(Request *);
private:
	vector<User*>*users;
};

class sign_chef : public RequestHandler {
public:
	sign_chef(vector<User*>* user, int *id) { users = user; user_id = id; }
	Response *callback(Request *);
private:
	vector<User*>*users;
	int *user_id;
};

class sign_user : public RequestHandler {
public:
	sign_user(vector<User*>* user, int *id) { users = user; user_id = id; }
	Response *callback(Request *);
private:
	vector<User*>*users;
	int *user_id;
};

class Plogin : public RequestHandler {
public:
	Plogin(vector<User*> *user, int *id, vector<recipe>*recipe, int &rid) { users = user; user_id = id; recipes = recipe; recipe_id = rid; }
	Response *callback(Request *);
private:
	vector<User*>*users;
	vector<recipe>*recipes;
	int *user_id;
	int recipe_id;
};

class RecipeHandler : public RequestHandler {
public:
	RecipeHandler( vector<recipe>*recipe, int *rid) {recipes = recipe; recipe_id = rid; }
	Response *callback(Request *);
private:
	vector<recipe>*recipes;
	int *recipe_id;
};

class del_recipe_Handler : public RequestHandler {
public:
	del_recipe_Handler(vector<recipe>*recipe) { recipes = recipe;  }
	Response *callback(Request *);
private:
	vector<recipe>*recipes;
};

class MoreRecipeHandler : public RequestHandler {
public:
	MoreRecipeHandler(vector<recipe>*recipe) { recipes = recipe; }
	Response *callback(Request *);
private:
	vector<recipe>*recipes;
};

class ScoreRecipeHandler : public RequestHandler {
public:
	ScoreRecipeHandler(vector<recipe>*recipe) { recipes = recipe; }
	Response *callback(Request *);
private:
	vector<recipe>*recipes;
};

class ShelfManage : public RequestHandler {
public:
	ShelfManage(vector<recipe>*recipe, vector<shelf>*shelve, int *id) { recipes = recipe; shelves = shelve; shelf_id = id; }
	Response *callback(Request *);
private:
	vector<recipe>*recipes;
	vector<shelf>*shelves;
	int *shelf_id;
};

class ShelfHandler : public RequestHandler {
public:
	ShelfHandler(vector<shelf>*shelve, int *id) { shelves = shelve; shelf_id = id; }
	Response *callback(Request *);
private:
	vector<shelf>*shelves;
	int *shelf_id;
};

class ScoreRecipee : public RequestHandler {
public:
	Response *callback(Request *);
private:
	
};

int getSCORE(vector<float>score);

#endif
