#include "kvstore.h"
#include <string>

bool less(uint64_t k1, uint64_t k2) { return k1 < k2; }
bool equal(uint64_t k1, uint64_t k2) { return k1 == k2; }
KVStore::KVStore(const std::string &dir) : KVStoreAPI(dir) {
    memtable.less = less;
    memtable.equal = equal;
}

KVStore::~KVStore() { memtable.~SkipList(); }

/**
 * Insert/Update the key-value pair.
 * No return values for simplicity.
 */
void KVStore::put(uint64_t key, const std::string &s) {
    memtable.insert(key, s);
}
/**
 * Returns the (string) value of the given key.
 * An empty string indicates not found.
 */
std::string KVStore::get(uint64_t key) { return memtable.search(key); }
/**
 * Delete the given key-value pair if it exists.
 * Returns false iff the key is not found.
 */
bool KVStore::del(uint64_t key) { return memtable.remove(key); }

/**
 * This resets the kvstore. All key-value pairs should be removed,
 * including memtable and all sstables files.
 */
void KVStore::reset() { memtable.~SkipList(); }
