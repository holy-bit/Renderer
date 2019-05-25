/////////////////////////////
	//Author: Luis Chamarro Alonso
	//Date: 15/02/2019
	//Videojuegos-Esne: 4.3

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <vector>
    #include <Point.hpp>
    #include "Rasterizer.hpp"
    #include "Color_Buffer_Rgb565.hpp"
    #include "Color_Buffer_Rgba8888.hpp"
	#include "Obj_Loader.hpp"

    namespace renderer
    {
        class View
        {
        private:

            typedef Color_Buffer_Rgba8888 Color_Buffer;
            typedef Color_Buffer::Color   Color;
           
        private:

            size_t width;	/**< Ancho de la pantalla */ 
            size_t height;	/**< Alto de la pantalla */

            Color_Buffer               Color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

			vector<Model> models; /**< Lista de los modelos en la view */

        public:

            View(size_t width, size_t height);

            void update ();
            void paint  ();

        };

    }

#endif
