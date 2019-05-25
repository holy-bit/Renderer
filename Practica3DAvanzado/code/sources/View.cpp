/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
	//Videojuegos-Esne: 4.3

#include <cmath>
#include <cassert>

#include "View.hpp"
#include <Vector.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>



using namespace toolkit;

namespace renderer
{
	/**
	* Al crear el view (escena) por comodidad cargo los modelos y manipulo los valores de su
	* transform para determinar su posicion, rotacion y escala.
	*/
    View::View(size_t width, size_t height)
    :
        width       (width ),
        height      (height),
        Color_buffer(width, height),
        rasterizer  (Color_buffer )
    {		
		models.push_back(Obj_Loader("..//..//assets//sources//wolf.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//wolf.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//base.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//moon.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//emptyObject.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//star.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//star.obj"));
		models.push_back(Obj_Loader("..//..//assets//sources//star.obj"));

		models[1].setParent(models[2].getModel());
		models[0].setParent(models[2].getModel());
		models[4].setParent(models[3].getModel());
		models[5].setParent(models[4].getModel());
		models[6].setParent(models[4].getModel());
		models[7].setParent(models[4].getModel());
		
		
		models[0].transform.scaling = 3.f;
		models[1].transform.scaling = 2.f;
		models[2].transform.scaling = 0.2f;
		models[3].transform.scaling = 0.2f;
		models[5].transform.scaling = 0.2f;
		models[6].transform.scaling = 0.2f;
		models[7].transform.scaling = 0.2f;


		models[0].transform.translation = Translation3f(0, 0, -100);
		models[1].transform.translation = Translation3f(0, 0, -100);
		models[2].transform.translation = Translation3f(0, -3, -30);
		models[3].transform.translation = Translation3f(-6, 2, -30);
		models[5].transform.translation = Translation3f(0,0,10);
		models[6].transform.translation = Translation3f(-6, 10, 0);
		models[7].transform.translation = Translation3f(10, 0, 0);

    }

	/**
	*	En el update del view muevo a tiempo real los modelos que quiero que se muevan y llamo a los updates de cada uno de ellos.
	*/
    void View::update ()
    {
		// Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

		static float angle = 0.f;

		angle += 0.05f;

		// Se borra el framebúffer y se dibujan los triángulos:
		rasterizer.clear();

		for (Model& model : models) model.update();

		//Modifico manualmente el movimiento de los distintos modelos, para hacerlo de forma sencilla.
		models[2].rotateY(angle);
		models[4].rotateY(angle);
		models[4].rotateX(angle);
		models[5].rotateY(angle);
		models[6].rotateY(angle);
		models[7].rotateY(angle);
		models[0].transform.translation = Translation3f(0, 7, 0);
		models[1].transform.translation = Translation3f(0, 6, 10);

       
    }

    void View::paint ()
    {

		for (Model& model : models) model.render(rasterizer);
       
    }

}
