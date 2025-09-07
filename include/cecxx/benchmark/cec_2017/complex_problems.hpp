#pragma once

#include <cecxx/benchmark/cec_2017/basic_problems.hpp>
#include <cecxx/benchmark/cec_2017/hybrid_problems.hpp>
#include <cecxx/benchmark/detail/problem_invokers/complex_problem_invoker.hpp>

namespace cecxx::benchmark::cec_2017 {

const auto complex_1 = detail::complex_problem_invoker{std::tuple{basic::rosenbrock, basic::ellips, basic::rastrigin},
                                                       {.deltas = {10.0, 20.0, 30.0},
                                                        .biases = {0.0, 100.0, 200.0},
                                                        .masks = {
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                        },
                                                        .scales = {
                                                            {1.0, 1.0},
                                                            {10000, 1e+10},
                                                            {1.0, 1.0},
                                                        }}};

const auto complex_2 = detail::complex_problem_invoker{std::tuple{basic::rastrigin, basic::griewank, basic::schwefel},
                                                       {.deltas = {10.0, 20.0, 30.0},
                                                        .biases = {0.0, 100.0, 200.0},
                                                        .masks = {
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                        },
                                                        .scales = {
                                                            {1.0, 1.0},
                                                            {1000, 100},
                                                            {1.0, 1.0},
                                                        }}};

const auto complex_3 = detail::complex_problem_invoker{std::tuple{basic::rosenbrock, basic::ackley, basic::schwefel, basic::rastrigin},
                                                       {.deltas = {10.0, 20.0, 30.0, 40.0},
                                                        .biases = {0.0, 100.0, 200.0, 300.0},
                                                        .masks = {
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                        },
                                                        .scales = {
                                                            {1.0, 1.0},
                                                            {1000, 100},
                                                            {1.0, 1.0},
                                                            {1.0, 1.0},
                                                        }}};

const auto complex_4 = detail::complex_problem_invoker{std::tuple{basic::ackley, basic::ellips, basic::griewank, basic::rastrigin},
                                                       {.deltas = {10.0, 20.0, 30.0, 40.0},
                                                        .biases = {0.0, 100.0, 200.0, 300.0},
                                                        .masks = {
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                        },

                                                        .scales = {
                                                            {1000, 100},
                                                            {10000, 1e+10},
                                                            {1000, 100},
                                                            {1.0, 1.0},
                                                        }}};

const auto complex_5 = detail::complex_problem_invoker{std::tuple{basic::rastrigin, basic::happycat, basic::ackley, basic::discus, basic::rosenbrock},
                                                       {.deltas = {10.0, 20.0, 30.0, 40.0, 50.0},
                                                        .biases = {0.0, 100.0, 200.0, 300.0, 400.0},
                                                        .masks = {
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                        },
                                                        .scales = {
                                                            {10000, 1e+3},
                                                            {1000, 1e+3},
                                                            {1000, 100},
                                                            {10000, 1e+10},
                                                            {1.0, 1.0}
                                                        }}};

const auto complex_6 = detail::complex_problem_invoker{std::tuple{basic::escaffer, basic::schwefel, basic::griewank, basic::rosenbrock, basic::rastrigin},
                                                       {.deltas = {10.0, 20.0, 20.0, 30.0, 40.0},
                                                        .biases = {0.0, 100.0, 200.0, 300.0, 400.0},
                                                        .masks = {
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                          {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                        },
                                                       .scales = {
                                                            {1e4, 2e+7},
                                                            {1.0, 1.0},
                                                            {1000, 100},
                                                            {1.0, 1.0},
                                                            {10000, 1e+3},
                                                        }}};

const auto complex_7 = detail::complex_problem_invoker{
    std::tuple{basic::hgbat, basic::rastrigin, basic::schwefel, basic::bent_cigar, basic::ellips, basic::escaffer},
    {.deltas = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0},
     .biases = {0.0, 100.0, 200.0, 300.0, 400.0, 500.0},
     .masks = {{.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes}},

     .scales = {
         {10000, 1000},
         {10000, 1e+3},
         {10000, 4e3},
         {10000, 1e+30},
         {10000, 1e+10},
         {10000, 2e7},
     }}};

const auto complex_8 = detail::complex_problem_invoker{
    std::tuple{basic::ackley, basic::griewank, basic::discus, basic::rosenbrock, basic::happycat, basic::escaffer},
    {.deltas = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0},
     .biases = {0.0, 100.0, 200.0, 300.0, 400.0, 500.0},
     .masks = {{.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
               {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes}},
     .scales = {
         {1000, 100},
         {1000, 100},
         {10000, 1e+10},
         {1.0, 1.0},
         {1000, 1e+3},
         {10000, 2e+7},
     }}};

const auto complex_9
    = detail::complex_problem_invoker{std::tuple{hybrid_5, hybrid_6, hybrid_7},
                                      {.deltas = {10.0, 30.0, 50.0},
                                       .biases = {0.0, 100.0, 200.0},
                                       .masks = {{.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                 {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                 {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes}},
                                       .scales = {{1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}}}};

const auto complex_10
    = detail::complex_problem_invoker{std::tuple{hybrid_5, hybrid_8, hybrid_9},
                                      {.deltas = {10.0, 30.0, 50.0},
                                       .biases = {0.0, 100.0, 200.0},
                                       .masks = {{.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                 {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes},
                                                 {.rot = do_affine_trans::yes, .shift = do_affine_trans::yes}},
                                       .scales = {{1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}}}};
} // namespace cecxx::benchmark::cec_2017
