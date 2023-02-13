#include"BartaGraph.h"
#include <SFML/Graphics.hpp>
#include"log.h"

int main(){

    Barta::Application* app = new BartaGraph();
    app->run();
    delete app;

    return 0;
}