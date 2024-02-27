/**
 * @file numcal.hpp
 * @author zhaoxi (535394140@qq.com)
 * @brief Numerical Calculation Module 数值计算模块
 * @version 1.0
 * @date 2024-01-06
 *
 * @copyright Copyright 2023 (c), zhaoxi
 *
 */

#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>

//! @addtogroup core
//! @{
//! @defgroup core_numcal 数值计算模块
//! @{
//! @brief 包含函数插值、曲线拟合、非线性方程（组）数值解、常微分方程数值解等数值计算算法
//! @} core_numcal
//! @} core

namespace rm
{

//! @addtogroup core_numcal
//! @{

//! N 次多项式
class Polynomial
{
    std::vector<double> _coeffs; //!< 多项式系数

public:
    /**
     * @brief 创建多项式对象
     * @brief
     * - 多项式系数 \f$a_0,a_1,\cdots,a_{N-1}\f$ 用来表示多项式 \f$f(x)=a_0+a_1x+\cdots+a_{N-1}x^{N-1}\f$
     *
     * @param[in] coeffs 多项式系数 \f$a_0,a_1,\cdots,a_{N-1}\f$
     */
    Polynomial(const std::initializer_list<double> &coeffs) : _coeffs(coeffs) {}

    /**
     * @brief 指定多项式阶数创建多项式对象
     *
     * @param[in] order 多项式阶数，即多项式的最高次数
     */
    Polynomial(size_t order) : _coeffs(order + 1) {}

    /**
     * @brief 计算多项式在指定点的函数值
     *
     * @param[in] x 指定点的 x 坐标
     * @return 多项式在指定点的函数值
     */
    inline double operator()(double x) const noexcept
    {
        double y = _coeffs.back();
        std::for_each(_coeffs.rbegin() + 1, _coeffs.rend(), [&](double val) { y = y * x + val; });
        return y;
    }
};

///////////////////// 函数插值 /////////////////////

/**
 * @brief 函数插值器
 * @brief
 * - 由于插值多项式具有唯一性，为了提高新增节点时算法的简易性，这里使用 Newton 插值多项式
 */
class Interpolator
{
    std::vector<double> _xs;                    //!< 插值节点
    std::vector<std::vector<double>> _diffquot; //!< 差商表

public:
    Interpolator() = default;

    /**
     * @brief 创建插值器对象，初始化差商表
     *
     * @param[in] xs 已知节点的 x 坐标 \f$x_0,x_1,\cdots,x_n\f$
     * @param[in] ys 已知节点的 y 坐标 \f$f(x_0),f(x_1),\cdots,f(x_n)\f$
     */
    Interpolator(const std::vector<double> &xs, const std::vector<double> &ys);

    /**
     * @brief 添加新的插值节点
     *
     * @param[in] x 新的插值节点的 x 坐标
     * @param[in] y 新的插值节点的 y 坐标
     * @code{.cpp}
     * Interpolator interf;
     * // 可以链式添加多个插值节点
     * interf.add(4, 16).add(5, 25).add(6, 36);
     * @endcode
     */
    Interpolator &add(double x, double y);

    /**
     * @brief 计算插值多项式在指定点的函数值
     *
     * @param[in] x 指定点的 x 坐标
     * @return 插值多项式在指定点的函数值
     */
    double operator()(double x) const;
};

///////////////////// 曲线拟合 /////////////////////

/**
 * @brief 曲线拟合器
 * @brief
 * - 使用最小二乘法拟合曲线，详见 @ref tutorial_modules_least_square
 */
class CurveFitter
{
    std::vector<std::size_t> _idx; //!< 拟合曲线的阶数（从低到高）
    std::vector<double> _coeffs;   //!< 拟合曲线的系数

public:
    /**
     * @brief 创建曲线拟合器对象
     *
     * @param[in] xs 已知节点的 x 坐标列表 \f$\text{xs}=\{x_0,x_1,\cdots,x_n\}\f$
     * @param[in] ys 已知节点的 y 坐标列表 \f$\text{ys}=\{f(x_0),f(x_1),\cdots,f(x_n)\}\f$
     * @param[in] order 拟合曲线的阶数，参数从最 **低** 位到最 **高** 位依次为 a0 ~ a7，即
     *                  \f[f(x)=a_0+a_1x+\cdots+a_7x^7\tag1\f]例如 `0b01000101` 表示拟合曲线为
     *                  \f[f(x)=a_0+a_2x^2+a_6x^6\tag2\f]
     */
    CurveFitter(const std::vector<double> &xs, const std::vector<double> &ys, std::bitset<8> order);

    /**
     * @brief 计算拟合曲线在指定点的函数值
     *
     * @param[in] x 指定点的 x 坐标
     * @return 拟合曲线在指定点的函数值
     */
    double operator()(double x) const;
};

///////////////// 非线性方程数值解 /////////////////

/**
 * @brief 非线性方程求解器
 * @brief
 * - 使用离散 Newton 迭代法求解非线性方程，详见 @ref tutorial_modules_func_iteration
 */
class NonlinearSolver
{
    std::function<double(double)> _func; //!< 非线性方程函数对象

public:
    NonlinearSolver() = default;

    /**
     * @brief 创建非线性方程求解器对象
     *
     * @param[in] f 非线性方程 \f$f(x)=0\f$ 的函数对象 \f$f(x)\f$
     * @note
     * - 可以是函数指针、函数对象、lambda 表达式等，可隐式转换为 `double (*)(double)`
     */
    NonlinearSolver(const std::function<double(double)> &f) : _func(f) {}

    /**
     * @brief 修改非线性方程 \f$f(x)=0\f$ 的函数对象
     *
     * @param[in] f 非线性方程 \f$f(x)=0\f$ 的函数对象 \f$f(x)\f$
     * @note
     * - 可以是函数指针、函数对象、lambda 表达式等，可隐式转换为 `double (*)(double)`
     */
    void operator=(const std::function<double(double)> &f) { _func = f; }

    /**
     * @brief 使用离散 Newton 迭代法求解非线性方程 \f$f(x)=0\f$
     *
     * @param[in] x0 迭代初始值
     * @param[in] eps 精度要求
     * @param[in] max_iter 最大迭代次数
     * @return 迭代结果
     */
    double operator()(double x0, double eps = 1e-5, std::size_t max_iter = 50) const;
};

////////////// 常微分方程（组）数值解 //////////////

//! Runge-Kutta 阶数类型
enum class RkType
{
    Butcher, //!< 指定 `Butcher` 表的 Runge-Kutta 法
    RK2,     //!< 2 阶 2 级 Runge-Kutta 方法（中点公式）
    RK3,     //!< 3 阶 3 级 Runge-Kutta 方法
    RK4,     //!< 4 阶 4 级 Runge-Kutta 方法（经典 Runge-Kutta 公式）
};

//! 常微分方程
using Ode = std::function<double(double, const std::vector<double> &)>;
//! 常微分方程组
using Odes = std::vector<Ode>;

/**
 * @brief 常微分方程（组）数值求解器
 * @brief
 * - 使用 Runge-Kutta 法求解常微分方程（组），算法介绍见 @ref tutorial_modules_runge_kutta
 * @brief
 * - 包含 4 个特化模板类，分别对应 4 阶 4 级、3 阶 3 级、2 阶 2 级、Butcher 表 Runge-Kutta 求解器，其中通用求解器为
 *   `rm::RungeKutta<RkType::Butcher>`，其他 3 个模板类均继承自该模板类，并提供了固定的 Butcher 表参数
 *
 * @tparam OrderType Runge-Kutta 阶数类型
 */
template <RkType OrderType>
class RungeKutta;

/**
 * @brief Butcher 表 Runge-Kutta 求解器
 * @brief
 * - 算法介绍见 @ref tutorial_modules_runge_kutta
 */
template <>
class RungeKutta<RkType::Butcher>
{
    // 加权系数，`k[i][j]`: `i` 表示第 `i` 个加权系数组，`j` 表示来自第 `j` 条方程
    std::vector<std::vector<double>> _ks;

protected:
    //! 一阶常微分方程组的函数对象 \f$\dot{\pmb x}=\pmb F(t, \pmb x)\f$
    Odes _fs;
    double _t0;              //!< 初值的自变量 \f$t\f$
    std::vector<double> _x0; //!< 初值的因变量 \f$\pmb x(t)\f$

    std::vector<double> _p;              //!< Butcher 表 \f$\pmb p\f$ 向量
    std::vector<double> _lambda;         //!< Butcher 表 \f$\pmb\lambda\f$ 向量
    std::vector<std::vector<double>> _r; //!< Butcher 表 \f$R\f$ 矩阵

public:
    /**
     * @brief 创建一阶常微分方程（组）数值求解器对象，设置初值请参考 @ref init 方法
     *
     * @param[in] fs 常微分方程（组）\f$\pmb x'=\pmb F(t,\pmb x)\f$ 的函数对象 \f$\pmb F(t,\pmb x)\f$
     * @param[in] p Butcher 表 \f$\pmb p\f$ 向量
     * @param[in] lambda Butcher 表 \f$\pmb\lambda\f$ 向量
     * @param[in] r Butcher 表 \f$R\f$ 矩阵
     */
    RungeKutta(const Odes &fs, const std::vector<double> &p,
               const std::vector<double> &lambda, const std::vector<std::vector<double>> &r);

    /**
     * @brief 设置常微分方程（组）的初值
     *
     * @param[in] t0 初始位置的自变量 \f$t\f$
     * @param[in] x0 初始位置的因变量 \f$\pmb x(t_0)\f$
     */
    inline void init(double t0, const std::vector<double> &x0) { _t0 = t0, _x0 = x0; }

    /**
     * @brief 设置常微分方程（组）的初值
     *
     * @param[in] t0 初始位置的自变量 \f$t\f$
     * @param[in] x0 初始位置的因变量 \f$\pmb x(t_0)\f$
     */
    inline void init(double t0, std::vector<double> &&x0) { _t0 = t0, _x0 = std::move(x0); }

    /**
     * @brief 计算常微分方程（组）的数值解
     *
     * @param[in] h 步长
     * @param[in] n 迭代次数
     *
     * @return 从初始位置开始迭代 \f$n\f$ 次后共 \f$n+1\f$ 个数值解，自变量可通过 \f$t_0+ih\f$ 计算得到
     */
    std::vector<std::vector<double>> solve(double h, std::size_t n);

#if __cpp_lib_generator >= 202207L
    /**
     * @brief 常微分方程（组）数值解生成器
     *
     * @param[in] h 步长
     * @param[in] n 迭代次数
     * @return 从初始位置开始迭代计算的生成器，初值不会被 `co_yield`，共生成 \f$n\f$ 个数值解
     */
    std::generator<std::vector<double>> generate(double h, std::size_t n);
#endif
};

//! @} core_numcal

RungeKutta(const Odes &, const std::vector<double> &, const std::vector<double> &,
           const std::vector<std::vector<double>> &) -> RungeKutta<RkType::Butcher>;

//! @addtogroup core_numcal
//! @{

//! 2 阶 2 级 Runge-Kutta 求解器
template <>
class RungeKutta<RkType::RK2> : public RungeKutta<RkType::Butcher>
{
public:
    /**
     * @brief 创建 2 阶 2 级 Runge-Kutta 常微分方程（组）数值求解器对象，设置初值请参考 @ref init 方法
     *
     * @param[in] fs 常微分方程（组）\f$\pmb x'=\pmb F(t,\pmb x)\f$ 的函数对象 \f$\pmb F(t,\pmb x)\f$
     */
    RungeKutta(const Odes &fs);
};

//! 3 阶 3 级 Runge-Kutta 求解器
template <>
class RungeKutta<RkType::RK3> : public RungeKutta<RkType::Butcher>
{
public:
    /**
     * @brief 创建 3 阶 3 级 Runge-Kutta 常微分方程（组）数值求解器对象，设置初值请参考 @ref init 方法
     *
     * @param[in] fs 常微分方程（组）\f$\pmb x'=\pmb F(t,\pmb x)\f$ 的函数对象 \f$\pmb F(t,\pmb x)\f$
     */
    RungeKutta(const Odes &fs);
};

//! 4 阶 4 级 Runge-Kutta 求解器
template <>
class RungeKutta<RkType::RK4> : public RungeKutta<RkType::Butcher>
{
public:
    /**
     * @brief 创建 4 阶 4 级 Runge-Kutta 常微分方程（组）数值求解器对象，设置初值请参考 @ref init 方法
     *
     * @param[in] fs 常微分方程（组）\f$\pmb x'=\pmb F(t,\pmb x)\f$ 的函数对象 \f$\pmb F(t,\pmb x)\f$
     */
    RungeKutta(const Odes &fs);
};

//! @} core_numcal

} // namespace rm
