template <typename tCoste>
vector<tCoste> DijkstraInverso(const GrafoP<tCoste>& G,
                        typename GrafoP<tCoste>::vertice destino,
                        vector<typename GrafoP<tCoste>::vertice>& P)
// Calcula los caminos de coste mínimo entre origen y todos los
// vértices del grafo G. En el vector D de tamaño G.numVert()
// devuelve estos costes mínimos y P es un vector de tamaño
// G.numVert() tal que P[i] es el último vértice del camino
// de origen a i.
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false);                  // Conjunto de vértices vacío.
   vector<tCoste> D(n);                          // Costes mínimos desde origen.

   // Iniciar D y P con caminos directos desde el vértice origen.
   for (size_t i = 0; i<n,i++)
      D[i]=G[i][destino];
   D[destino]=0;
   P = vector<vertice>(n, destino);

   S[destino] = true;                          // Incluir vértice origen en S.
   for (size_t i = 1; i <= n-2; i++) {
      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for (v = 0; v < n; v++)
         if (!S[v] && D[v] <= costeMin) {
            costeMin = D[v];
            w = v;
         }
      S[w] = true;                          // Incluir vértice w en S.
      // Recalcular coste hasta cada v no incluido en S a través de w.
      for (v = 0; v < n; v++)
         if (!S[v]) {
            tCoste vwd = suma(G[v][w],D[w]);
            if (vwd < D[v]) {
               D[v] = vwd;
               P[v] = w;
            }
         }
   }
   return D;
}