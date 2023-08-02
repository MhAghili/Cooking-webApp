#include "handlers.hpp"
#include "my_server.hpp"
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

int main(int argc, char **argv) {
	vector<User*>users;
	vector<recipe>recipes;
	vector<shelf>shelves;
	string command;
	string empty;
	int recipe_id = 1;
	int shelf_id = 1;
	int user_curr = 0;
	int user_id = 1;
  srand(time(NULL)); // for rand
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    //server.get("/Plogin", new ShowPage("static/logincss.html"));
	server.get("/sign", new ShowPage("static/type.html"));
    server.get("/sign_chef", new ShowPage("static/upload_form_chef.html"));
	server.get("/sign_user", new ShowPage("static/upload_form_user.html"));
	server.post("/sign_user", new sign_chef(&users,&user_curr));
	server.post("/sign_chef", new sign_user(&users,&user_curr));
	server.get("/Plogin", new Plogin(&users, &user_curr, &recipes, recipe_id));
	server.post("/Plogin", new Plogin(&users, &user_curr,&recipes,recipe_id));
	server.get("/login", new ShowPage("static/upload_form_login.html"));
	server.post("/login", new LoginHandler(&users));
	server.get("/addrecipe", new ShowPage("static/addrecipe.html"));
	server.post("/addrecipe", new RecipeHandler(&recipes,&recipe_id));
	server.get("/", new ShowPage("static/home.html"));
	server.get("/MoreRecipe", new MoreRecipeHandler(&recipes));
	server.get("/ScoreRecipee", new ScoreRecipee());
	server.post("/ScoreRecipe", new ScoreRecipeHandler(&recipes));
	server.get("/DeleteRecipe", new del_recipe_Handler(&recipes));
	server.get("/ShelfManage", new ShelfManage(&recipes,&shelves,&shelf_id));
	server.get("/addshelf", new ShowPage("static/addshelf.html"));
	server.post("/addshelf", new ShelfHandler(&shelves, &shelf_id));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
