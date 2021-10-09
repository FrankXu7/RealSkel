#pragma once

#include <boost/graph/graph_traits.hpp>

#include "graph_circulator.h"

template <typename K>
class Surface_mesh;

namespace boost
{
    template <class P>
    struct graph_traits<Surface_mesh<P>>
    {
    private:
        typedef Surface_mesh<P> SM;

        struct SM_graph_traversal_category : public virtual boost::bidirectional_graph_tag,
                                             public virtual boost::vertex_list_graph_tag,
                                             public virtual boost::edge_list_graph_tag

        {
        };

    public:
        // Graph
        typedef boost::undirected_tag directed_category;
        typedef boost::disallow_parallel_edge_tag edge_parallel_category;
        typedef SM_graph_traversal_category traversal_category;

        typedef typename SM::Vertex_index vertex_descriptor;
        typedef typename SM::Point vertex_property_type;
        typedef typename SM::Edge_index edge_descriptor;
        typedef typename SM::Halfedge_index halfedge_descriptor;
        typedef typename SM::Face_index face_descriptor;

        typedef typename SM::Vertex_iterator vertex_iterator;
        typedef typename SM::size_type vertices_size_type;

        typedef typename SM::Edge_iterator edge_iterator;
        typedef typename SM::size_type edges_size_type;

        typedef typename SM::Halfedge_iterator halfedge_iterator;
        typedef typename SM::size_type halfedges_size_type;

        typedef typename SM::Face_iterator face_iterator;
        typedef typename SM::size_type faces_size_type;

        typedef typename SM::size_type degree_size_type;

        typedef EGL::In_edge_iterator<SM> in_edge_iterator;
        typedef EGL::Out_edge_iterator<SM> out_edge_iterator;

        // nulls
        static vertex_descriptor null_vertex() { return vertex_descriptor(); }
        static face_descriptor null_face() { return face_descriptor(); }
        static halfedge_descriptor null_halfedge() { return halfedge_descriptor(); }
    };

    template <class P>
    struct graph_traits<const Surface_mesh<P>>
        : public graph_traits<Surface_mesh<P>>
    {
    };
} // namespace boost

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertices_size_type
num_vertices(const Surface_mesh<P> &sm)
{
    return sm.num_vertices();
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::edges_size_type
num_edges(const Surface_mesh<P> &sm)
{
    return sm.num_edges();
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::degree_size_type
degree(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
       const Surface_mesh<P> &sm)
{
    return sm.degree(v);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::degree_size_type
degree(typename boost::graph_traits<Surface_mesh<P>>::face_descriptor f,
       const Surface_mesh<P> &sm)
{
    return sm.degree(f);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::degree_size_type
out_degree(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
           const Surface_mesh<P> &sm)
{
    return sm.degree(v);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::degree_size_type
in_degree(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
          const Surface_mesh<P> &sm)
{
    return sm.degree(v);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor
source(typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor e,
       const Surface_mesh<P> &sm)
{
    return sm.source(e.halfedge());
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor
source(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
       const Surface_mesh<P> &sm)
{
    return sm.source(h);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor
target(typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor e,
       const Surface_mesh<P> &sm)
{
    return sm.target(e.halfedge());
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor
target(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
       const Surface_mesh<P> &sm)
{
    return sm.target(h);
}

template <typename P>
Iterator_range<typename boost::graph_traits<Surface_mesh<P>>::vertex_iterator>
vertices(const Surface_mesh<P> &sm)
{
    return sm.vertices();
}

template <typename P>
Iterator_range<typename boost::graph_traits<Surface_mesh<P>>::halfedge_iterator>
halfedges(const Surface_mesh<P> &sm)
{
    return sm.halfedges();
}

template <typename P>
std::pair<typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor,
          bool>
edge(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor u,
     typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
     const Surface_mesh<P> &sm)
{
    typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor
        he(sm.halfedge(u, v));
    return std::make_pair(he, he.is_valid());
}

template <typename P>
Iterator_range<typename boost::graph_traits<Surface_mesh<P>>::edge_iterator>
edges(const Surface_mesh<P> &sm)
{
    return sm.edges();
}

template <typename P>
Iterator_range<typename boost::graph_traits<Surface_mesh<P>>::in_edge_iterator>
in_edges(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
         const Surface_mesh<P> &sm)
{
    typedef typename boost::graph_traits<Surface_mesh<P>>::in_edge_iterator Iter;

    return make_range(Iter(halfedge(v, sm), sm), Iter(halfedge(v, sm), sm, 1));
}

template <typename P>
Iterator_range<typename boost::graph_traits<Surface_mesh<P>>::out_edge_iterator>
out_edges(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
          const Surface_mesh<P> &sm)
{
    typedef typename boost::graph_traits<Surface_mesh<P>>::out_edge_iterator Iter;
    return make_range(Iter(halfedge(v, sm), sm), Iter(halfedge(v, sm), sm, 1));
}

//
// HalfedgeGraph
//
template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor
next(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
     const Surface_mesh<P> &sm)
{
    return sm.next(h);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor
prev(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
     const Surface_mesh<P> &sm)
{
    return sm.prev(h);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor
opposite(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
         const Surface_mesh<P> &sm)
{
    return sm.opposite(h);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor
edge(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
     const Surface_mesh<P> &sm)
{
    return sm.edge(h);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor
halfedge(typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor e,
         const Surface_mesh<P> &sm)
{
    return sm.halfedge(e);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor
halfedge(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
         const Surface_mesh<P> &sm)
{
    return sm.halfedge(v);
}

template <typename P>
std::pair<
    typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor,
    bool>
halfedge(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor u,
         typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
         const Surface_mesh<P> &sm)
{
    typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h = sm.halfedge(u, v);
    return std::make_pair(h, h.is_valid());
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedges_size_type
num_halfedges(const Surface_mesh<P> &sm)
{
    return sm.num_halfedges();
}

//
// MutableHalfedgeGraph
//
template <typename P>
void set_next(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h1,
              typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h2,
              Surface_mesh<P> &sm)
{
    sm.set_next(h1, h2);
}

template <typename P>
void set_target(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
                typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
                Surface_mesh<P> &sm)
{
    sm.set_target(h, v);
}

template <typename P>
void set_halfedge(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
                  typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
                  Surface_mesh<P> &sm)
{
    sm.set_halfedge(v, h);
}

template <typename P>
void collect_garbage(Surface_mesh<P> &sm)
{
    sm.collect_garbage();
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor
add_edge(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor u,
         typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
         Surface_mesh<P> &sm)
{
    return sm.edge(sm.add_edge(u, v));
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor
add_edge(Surface_mesh<P> &sm)
{
    return sm.edge(sm.add_edge());
}
//
// FaceGraph
//
template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor
halfedge(typename boost::graph_traits<Surface_mesh<P>>::face_descriptor f,
         const Surface_mesh<P> &sm)
{
    return sm.halfedge(f);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::face_descriptor
face(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
     const Surface_mesh<P> &sm)
{
    return sm.face(h);
}

//
// MutableFaceGraph
//
template <typename P>
void set_face(typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
              typename boost::graph_traits<Surface_mesh<P>>::face_descriptor f,
              Surface_mesh<P> &sm)
{
    sm.set_face(h, f);
}

template <typename P>
void set_halfedge(typename boost::graph_traits<Surface_mesh<P>>::face_descriptor f,
                  typename boost::graph_traits<Surface_mesh<P>>::halfedge_descriptor h,
                  Surface_mesh<P> &sm)
{
    sm.set_halfedge(f, h);
}

//
// FaceListGraph
//
template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::faces_size_type
num_faces(const Surface_mesh<P> &sm)
{
    return sm.num_faces();
}

template <typename P>
Iterator_range<typename boost::graph_traits<Surface_mesh<P>>::face_iterator>
faces(const Surface_mesh<P> &sm)
{
    return sm.faces();
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor
add_vertex(Surface_mesh<P> &sm)
{
    return sm.add_vertex();
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor
add_vertex(const typename boost::graph_traits<Surface_mesh<P>>::vertex_property_type &p, Surface_mesh<P> &sm)
{
    return sm.add_vertex(p);
}

// MutableGraph
template <typename P>
void reserve(Surface_mesh<P> &sm,
             typename boost::graph_traits<Surface_mesh<P>>::vertices_size_type nv,
             typename boost::graph_traits<Surface_mesh<P>>::edges_size_type ne,
             typename boost::graph_traits<Surface_mesh<P>>::faces_size_type nf)
{
    sm.reserve(nv, ne, nf);
}

template <typename P>
void remove_vertex(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
                   Surface_mesh<P> &sm)
{

    sm.remove_vertex(v);
}

template <typename P>
void remove_edge(typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor u,
                 typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor v,
                 Surface_mesh<P> &sm)
{
    typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor e = edge(u, v, sm);
    remove_edge(e, sm);
}

template <typename P>
void remove_edge(typename boost::graph_traits<Surface_mesh<P>>::edge_descriptor e,
                 Surface_mesh<P> &sm)
{
    sm.remove_edge(e);
}

template <typename P>
void remove_edge(typename boost::graph_traits<Surface_mesh<P>>::edge_iterator eiter,
                 Surface_mesh<P> &sm)
{
    remove_edge(*eiter, sm);
}

template <typename P>
void remove_face(typename boost::graph_traits<Surface_mesh<P>>::face_descriptor f,
                 Surface_mesh<P> &sm)
{

    sm.remove_face(f);
}

template <typename P>
typename boost::graph_traits<Surface_mesh<P>>::face_descriptor
add_face(Surface_mesh<P> &sm)
{
    return sm.add_face();
}

template <typename P, typename InputIterator>
typename boost::graph_traits<Surface_mesh<P>>::face_descriptor
add_face(InputIterator begin, InputIterator end, Surface_mesh<P> &sm)
{
    std::vector<typename boost::graph_traits<Surface_mesh<P>>::vertex_descriptor>
        v(begin, end);
    return sm.add_face(v);
}
