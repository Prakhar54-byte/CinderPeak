#pragma once
#include "StorageEngine/GraphContext.hpp"
#include "StorageEngine/Utils.hpp"

namespace CinderPeak {

template <typename V, typename E> struct AddEdgeOperation {

  CinderPeak::PeakStore::GraphContext<V, E> &ctx;

  const V &src;
  const V &dest;
  const E &weight;

  bool weighted;
  bool directed;

  CinderPeak::VertexId src_id{0};
  CinderPeak::VertexId dest_id{0};
  bool has_cached_ids{false};
};
} // namespace CinderPeak