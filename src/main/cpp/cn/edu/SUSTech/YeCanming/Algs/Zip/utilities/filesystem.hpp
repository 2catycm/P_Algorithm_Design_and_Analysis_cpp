//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include <filesystem>
#include <stack>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    namespace stdfs = std::filesystem;
    namespace filesystem {
        static constexpr char preferred_separator = '/'; //instead of '\\'
        /**
         * We use the iterative preorder traversal algorithm to improve performance.
         * Instead of recursion, which may break down when the file system is too large,
         * this algorithm exploits the properties of the tree structure and stack structure.
         * For preorder traversal this is easy because it was a tail recursion.
         * @tparam Lambda type of the file visitor lambda function.
         * @param path the root path you want to search.
         * @param fileVisitor a lambda function which will execute on every path found in the tree.
         * @return file_visited
         */
        template<typename Lambda>
        bool preorderTraversal(const stdfs::path &path, const Lambda &fileVisitor) {
            std::stack<stdfs::path> S;
            if (!stdfs::exists(path))
                return false;
            S.emplace(path);
            while (!S.empty()) {
                auto current_path = S.top();
                S.pop();
                if(!fileVisitor(current_path))
                    return false;
                if (stdfs::is_directory(current_path))
                    for (auto &p : stdfs::directory_iterator(current_path))
                        S.emplace(p.path());
            }
            return true;
        }
        //TODO post order traversal. (may be it is hard to be iterative because it is not a binary tree. )
    }// namespace filesystem
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::Utilities