#include "handlers.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> 
#include <sstream>
#include <cmath>
#include<iomanip>

using namespace std;

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *LoginHandler::callback(Request *req) {
	int flag = 0;
	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	for (int i = 0; i < users->size(); i++) {
		if (users->at(i)->get_username() == username &&users->at(i)->get_password() == password) {
			flag = 1;
		}
	}
	if (flag == 1) {
		Response *res = Response::redirect("/Plogin");
		res->setSessionId(username);
		return res;
	}
	else {
		Response *res = Response::redirect("/login");
		return res;
	}
}

Response *sign_user::callback(Request *req) {
	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	normal_user*new_user = new normal_user(username, password,*user_id);
	users->push_back(new_user);
	cout << "username: " << username << ",\tpassword: " << password << endl;
	Response *res = Response::redirect("/Plogin");
	res->setSessionId(username);
	return res;
}

Response *sign_chef::callback(Request *req) {
	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	chef*new_chef = new chef(username, password,*user_id);
	users->push_back(new_chef);
	cout << "username: " << username << ",\tpassword: " << password << endl;
	Response *res = Response::redirect("/Plogin");
	res->setSessionId(username);
	return res;
}

Response *Plogin::callback(Request *req) {
	string name = req->getSessionId();
	User*curr;
	for (int i = 0; i < users->size(); i++) {
		if (users->at(i)->get_username() == name) {
			curr = users->at(i);
			break;
		}
	}
	string ff = to_string(recipes->size());
	if (curr->get_type() == "user") {
		Response *res = new Response;
		res->setHeader("Content-Type", "text/html");
		string body;
		body += "<!DOCTYPE html>";
		body += "<html>";
		body += "<body style=\"text-align: center;\">";
		body += "<h1>HI ";
		body += req->getSessionId();
		body += "</h1>";
		if (recipes->size() != 0) {
			body += "<table border=1>";
			body += "<tr>";
			body += "<th>ID";
			body += "<th>title";
			body += "<th>vegetarian";
			body += "<th>minutes to ready";
			body += "<th>ingredients";
			body += "<th>tags";
			body += "<th>rating";
			body += "<th>Edit";
			body += "</tr>";
		}
		for (int i = 0; i < recipes->size(); i++) {
			if (curr->get_username() == recipes->at(i).get_chef()) {
				body += "<tr>";
				body += "<td>";
				string id = to_string(recipes->at(i).get_id());
				body += id;
				body += "<td>";
				body += recipes->at(i).get_title();
				body += "<td>";
				body += recipes->at(i).get_vegetarian();
				body += "<td>";
				body += recipes->at(i).get_min_to_ready();
				body += "<td>";
				body += recipes->at(i).get_ingredients();
				body += "<td>";
				body += recipes->at(i).get_tags();
				body += "<td>";
				string score = to_string(getSCORE(recipes->at(i).get_score()));
				body += score;
				body += "<td >";
				body += "<a href = '/DeleteRecipe?id=";
				body += id;
				body += "'>";
				body += "Delete</a>";
				body += "</tr>";
			}
		}
		body += "<a>";
		body += "<br / >";
		body += "<a href = '/addrecipe' > ";
		res->setSessionId(curr->get_username());
		body += "ADD Recipe</a>";
		body += "<a>";
		body += "<br / >";
		body += "<a href = '/' > ";
		body += "BACK</a>";
		body += "</body>";
		body += "</html>";
		res->setBody(body);
		return res;
	}
	if (curr->get_type() == "chef") {
		Response *res = new Response;
		res->setHeader("Content-Type", "text/html");
		string body;

		body += "<!DOCTYPE html>";
		body += "<html>";
		body += "<body style=\"text-align: center;\">";
		body += "<h1>HI ";
		body += req->getSessionId();
		body += "</h1>";
		body += "<h1>Recipes: ";
		body += "</h1>";
		if (recipes->size() != 0) {
			body += "<table border=1>";
			body += "<tr>";
			body += "<th>ID";
			body += "<th>title";
			body += "<th>vegetarian";
			body += "<th>minutes to ready";
			body += "<th>More";
			body += "</tr>";
		}
		for (int i = 0; i < recipes->size(); i++) {
			body += "<tr>";
			body += "<td>";
			string id = to_string(recipes->at(i).get_id());
			body += id;
			body += "<td>";
			body += recipes->at(i).get_title();
			body += "<td>";
			body += recipes->at(i).get_vegetarian();
			body += "<td>";
			body += recipes->at(i).get_min_to_ready();
			body += "<td >";
			body += "<a href = '/MoreRecipe?id=";
			body += id;
			body += "'>";
			body += "More</a>";
			body += "</tr>";
		}
		body += "<br / >";
		body += "<a href = '/ShelfManage?name=";
		body += name;
		res->setSessionId(name);
		body += "'>";
		body += "Shelf Manage</a>";
		body += "<br / >";
		body += "<a href = '/' > ";
		body += "BACK</a>";
		body += "</body>";
		body += "</html>";
		res->setBody(body);
		return res;
	}
}


Response *MoreRecipeHandler::callback(Request *req) {
	string ids = req->getQueryParam("id");
	stringstream geek(ids);
	int id = 0;
	geek >> id;
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<body style=\"text-align: center;\">";
		body += "<table border=1>";
		body += "<tr>";
		body += "<th>ID";
		body += "<th>title";
		body += "<th>vegetarian";
		body += "<th>minutes to ready";
		body += "<th>ingredients";
		body += "<th>tags";
		body += "<th>rating";
		body += "<th>Score";
		body += "</tr>";
	for (int i = 0; i < recipes->size(); i++) {
		if (id == recipes->at(i).get_id()) {
			body += "<tr>";
			body += "<td>";
			string id = to_string(recipes->at(i).get_id());
			body += id;
			body += "<td>";
			body += recipes->at(i).get_title();
			body += "<td>";
			body += recipes->at(i).get_vegetarian();
			body += "<td>";
			body += recipes->at(i).get_min_to_ready();
			body += "<td>";
			body += recipes->at(i).get_ingredients();
			body += "<td>";
			body += recipes->at(i).get_tags();
			body += "<td>";
			string score = to_string(getSCORE(recipes->at(i).get_score()));
			body += score;
			body += "<td >";
			body += "<a href = '/ScoreRecipee?id=";
			body += id;
			body += "'>";
			body += "Score Recipe</a>";
			body += "</tr>";
		}
	}
	body += "<br / >";
	body += "<a href = '/Plogin' > ";
	body += "BACK</a>";
	body += "</body>";
	body += "</html>";
	res->setBody(body);
	return res;
}



Response *RecipeHandler::callback(Request *req){
	string title = req->getBodyParam("title");
	string ingredients = req->getBodyParam("ingredients");
	string vegetarian = req->getBodyParam("vegetarian");
	string minutes_to_ready = req->getBodyParam("minutes_to_ready");
	string tags = req->getBodyParam("tags");
	string image_address = req->getBodyParam("image_address");
	string chef = req->getSessionId();
	recipes->push_back(recipe(*recipe_id, title, ingredients, vegetarian, minutes_to_ready, tags, image_address, chef));
	string ff = to_string(recipes->size());
	(*recipe_id)++;
	Response *res = new Response;
	res=Response::redirect("/Plogin");
	return res;
}

Response *ShelfHandler::callback(Request *req) {
	string name = req->getBodyParam("name");
	string user_name = req->getSessionId();
	shelves->push_back(shelf(name, *shelf_id, user_name));
	(*shelf_id)++;
	Response *res = new Response;
	res = Response::redirect("/ShelfManage?name="+ user_name);
	return res;
}


Response *del_recipe_Handler::callback(Request *req) {
	string ids = req->getQueryParam("id");
	stringstream geek(ids);
	int id = 0;
	geek >> id;
	for (int i = 0; i < recipes->size(); i++) {
		if (id == recipes->at(i).get_id()) {
			recipes->erase(recipes->begin() + i);
		}
	}
	Response *res = new Response;
	res = Response::redirect("/Plogin");
	return res;
}


Response *ScoreRecipeHandler::callback(Request *req) {
	string ids = req->getBodyParam("id");
	stringstream geek(ids);
	int id = 0;
	geek >> id;
	string idss = req->getBodyParam("score");
	stringstream geekk(idss);
	int score = 0;
	geekk >> score;
	for (int i = 0; i < recipes->size(); i++) {
		if (id == recipes->at(i).get_id()) {
			recipes->at(i).set_score(score);
		}
	}
	Response *res = new Response;
	res = Response::redirect("/Plogin");
	return res;
}

Response *ShelfManage::callback(Request *req) {
	string name = req->getQueryParam("name");
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<body style=\"text-align: center;\">";
	body += "<table border=1>";
	body += "<tr>";
	body += "<th>ID";
	body += "<th>title";
	body += "<th>More";
	body += "</tr>";
	for (int i = 0; i < shelves->size(); i++) {
		if (name == shelves->at(i).get_user()) {
			body += "<tr>";
			body += "<td>";
			string id = to_string(shelves->at(i).get_id());
			body += id;
			body += "<td>";
			body += shelves->at(i).get_name();
			body += "<td >";
			body += "<a href = '/moreshelf?id=";
			body += to_string(i);
			body += "'>";
			body += "More</a>";
			body += "</tr>";
		}
	}
	body += "<br / >";
	body += "<a href = '/addshelf";
	body += "'>";
	body += "Add shelf</a>";
	body += "<br / >";
	body += "<a href = '/Plogin' > ";
	body += "BACK</a>";
	body += "</body>";
	body += "</html>";
	res->setBody(body);
	return res;
}

Response *ScoreRecipee::callback(Request *req) {
	string ids = req->getQueryParam("id");
	stringstream geek(ids);
	int id = 0;
	geek >> id;
	string score;
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	ostringstream body;
	body
	<< "<html>" << endl
	<< "<head><title>Type your score</title></head>" << endl
	<< "<body>" << endl
	<< "    <p>" << endl
	<< "     your score:"<<endl
	<< "    </p>" << endl
    << "     <form action='/ScoreRecipe' method='POST'>" << endl
	<< "       <input type='hidden' name='id' value='" << id << "'/><br/>" << endl
	<< "       Score: <input type='text' name='score' value='" <<score<< "'/><br/>" << endl
	<< "       <input type='submit' value='OK'/>" << endl
	<< "   </form>" << endl
	<< "</body>" << endl
	<< "</html>" << endl;
	res->setBody(body.str());
	return res;
}


normal_user::normal_user(string b, string c,int id) :User(b, c, id) {}

chef::chef(string b, string c,int id) : User(b, c, id) {}

recipe::recipe(int a, string t, string b, string c, string d, string e, string f, string ch) {
	id = a;
	title = t;
	vegetarian = b;
	ingredients = c;
	min_to_ready = d;
	tags = e;
	img_adr = f;
	chef = ch;
}


void shelf::print() {
	cout << id << " " << name << endl;

}

void shelf::erase(int id) {
	for (int i = 0; i<recipee.size(); i++)
		if (id == recipee[i].get_id()) {
			recipee.erase(recipee.begin() + i);
			cout << "OK" << endl;
		}
}


void recipe::set_score(float a) {
	score.push_back(a);
}


int getSCORE(vector<float>score) {
	if (score.size() == 0)
		return 0;
	else {
		int sum = 0;
		for (int i = 0; i < score.size(); i++)
			sum = sum + score[i];
		int avarage = sum / score.size();
		return avarage;
	}
}