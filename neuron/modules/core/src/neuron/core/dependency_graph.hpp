#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace neuron {


    template <typename T>
    class DependencyGraph final {
      public:
        using key_t = T;

        DependencyGraph() = default;

        inline void add_dependency(key_t dependent, key_t dependency);
        inline void add_dependencies(key_t dependent, std::vector<key_t> dependencies);
        inline void add_dependencies(key_t dependent, std::unordered_set<key_t> dependencies);

        inline std::vector<key_t> generate_order() const;

      private:
        std::unordered_map<key_t, std::vector<key_t>> graph;
        std::unordered_map<key_t, std::vector<key_t>> inverse;
        std::unordered_set<key_t> nonroots;
        std::unordered_set<key_t> roots;
    };

    template <typename T>
    void DependencyGraph<T>::add_dependency(key_t dependent, key_t dependency) {
        nonroots.insert(dependent);
        roots.erase(dependent);

        if (const auto it = graph.find(dependency); it != graph.end()) {
            it->second.push_back(dependent);
        } else {
            graph.insert({dependency, {dependent}});
        }

        if (const auto it = inverse.find(dependent); it != inverse.end()) {
            it->second.push_back(dependency);
        } else {
            inverse.insert({dependent, {dependency}});
        }

        if (!nonroots.contains(dependency)) {
            roots.insert(dependency);
        }
    }

    template <typename T>
    void DependencyGraph<T>::add_dependencies(key_t dependent, std::vector<key_t> dependencies) {
        if (dependencies.empty() && !nonroots.contains(dependent)) {
            roots.insert(dependent);
        }

        for (const auto &dependency : dependencies) {
            add_dependency(dependent, dependency);
        }
    }

    template <typename T>
    void DependencyGraph<T>::add_dependencies(key_t dependent, std::unordered_set<key_t> dependencies) {
        if (dependencies.empty() && !nonroots.contains(dependent)) {
            roots.insert(dependent);
        }

        for (const auto &dependency : dependencies) {
            add_dependency(dependent, dependency);
        }
    }


    template <typename T>
    std::vector<typename DependencyGraph<T>::key_t> DependencyGraph<T>::generate_order() const {
        std::vector<key_t> order;
        std::unordered_set<key_t> seen;
        std::queue<key_t> queue;

        for (const auto &root : roots) {
            queue.push(root);
        }

        while (!queue.empty()) {
            const auto current = queue.front();
            queue.pop();

            if (seen.contains(current)) {
                continue; // assume that it got queued multiple times and ignore this
            }

            bool requeued = false;

            if (const auto& it = inverse.find(current); it != inverse.end()) {
                for (const auto& dependency : it->second) {
                    if (!seen.contains(dependency)) {
                        queue.push(current);
                        requeued = true;
                        break; // break out of this nested loop since we know we can't put it in the order yet.
                    }
                }
            }

            if (requeued) {
                continue;
            }

            // iterate over dependents, and add them to queue.
            if (const auto& it = graph.find(current); it != graph.end()) {
                for (const auto& dependent : it->second) {
                    queue.push(dependent);
                }
            }

            seen.insert(current);
            order.push_back(current);
        }

        return order;
    }
} // namespace neuron
