#ifndef ALG_GRAFO_P_H_V
#define ALG_GRAFO_P_H_V
#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
void visualizarGrafo(const GrafoP<tCoste>& G, std::string nombre)
/* VisualizarGrafo
*  Genera una imagen .png  a partir de un grafo ponderado representado mediante matriz de costes.
*  Para ello, se usa la biblioteca Graphviz y se genera un fichero .dot intermedio que se convierte en imagen a través de una llamada a sistema a graphviz (dot -Tpng ...)
*
*  @param G Grafo ponderado representado mediante una matriz de costes.
*  @param nombre Nombre sin extensión que se le dará a la imagen en formate png generada.
*
* Ejemplo: visualizarGrafo(Grafo, "Ej1")
*/
{
   std::ofstream img;
   typename GrafoP<tCoste>::vertice i, j;
   bool esdirigido = G.esDirigido();
   std::string dirigido_str;

   // Se crea y se comienza a editar el fichero .dot que contendrá la información del grafo.
   img.open(nombre + ".dot");
      
   // Configuración global de visualización, aspecto de los nodos y de las aristas
   img << (esdirigido ? "digraph" : "graph") << " G{" 
      << "\n\tlayout=neato;\n\trankdir=LR;\n\tbgcolor=white;" 
      << "\n\tgraph [ dpi = 300, splines=false, overlap=false, sep=\"+8\" ]; \n"
      << "\n\tnode [shape=circle, style=filled, fillcolor=\"#FFFFFF\", fontcolor=black, fontsize=16, penwidth=3];"
      << "\n\tedge [color=\"#36454F\", fontcolor=black, fontsize=16, style=solid, penwidth=2.5];\n";

   // Se incluyen los nodos en el grafo
   for(i = 0; i<G.numVert();i++){
      img << "\t" << std::to_string(i) + ";\n";     
   }

   // Se incluyen las aristas en el grafo. Se optimiza el proceso si el grafo es no dirigido.
   dirigido_str = (esdirigido ? " -> " : " -- ");
   for (i = 0; i < G.numVert(); i++)
   {
      j = esdirigido ? 0 : i;
      for (; j < G.numVert(); j++)
      {
         if (G[i][j] != GrafoP<tCoste>::INFINITO)
         {
               img << "\t" << std::to_string(i) + dirigido_str + std::to_string(j) + "[label=\"" + std::to_string(G[i][j]) + "\"];\n";
         }
      }
   }
   img << "}";
   img.close();

   // Se realiza la llamada al sistema a Graphviz y se genera la imagen con el nombre indicado
   std::system(("dot -Tpng " + nombre + ".dot -o " + nombre + ".png \n").c_str());
}


#endif