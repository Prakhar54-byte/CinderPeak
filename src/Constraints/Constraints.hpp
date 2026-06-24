#pragma once

#include "Operations/GraphOperations.hpp"
#include "StorageEngine/ErrorCodes.hpp"
namespace CinderPeak {
template <typename V, typename E>
PeakStatus validateAddEdge(AddEdgeOperation<V, E> &op) {

  auto *storage = op.ctx.active_storage.get();
  auto src_id_opt = storage->impl_lookupVertexId(op.src);
  auto dest_id_opt = storage->impl_lookupVertexId(op.dest);
  if (!src_id_opt || !dest_id_opt) {
    return PeakStatus::VertexNotFound("Source or destination vertex missing.");
  }

  op.src_id = *src_id_opt;
  op.dest_id = *dest_id_opt;
  op.has_cached_ids = true;

  if (op.src == op.dest) {
    return PeakStatus::InvalidArgument("Self loops are not allowed.");
  }

  bool exists = false;

  if (op.weighted) {

    exists = storage->impl_doesEdgeExist(op.src, op.dest, op.weight);

    if (!op.directed) {

      exists =
          exists || storage->impl_doesEdgeExist(op.dest, op.src, op.weight);
    }

  } else {

    exists = storage->impl_doesEdgeExist(op.src, op.dest);

    if (!op.directed) {

      exists = exists || storage->impl_doesEdgeExist(op.dest, op.src);
    }
  }

  if (exists) {

    return PeakStatus::EdgeAlreadyExists("Edge already exists.");
  }

  return PeakStatus::OK();
}
} // namespace CinderPeak