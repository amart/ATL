/* 
 * File:   Floor.hpp
 * Author: matthewsupernaw
 *
 * Created on June 18, 2014, 12:54 PM
 */

#ifndef ET4AD_FLOOR_HPP
#define	ET4AD_FLOOR_HPP

#include <cmath>
#include "Expression.hpp"

namespace atl {

    /**
     * Expression template for handling the floor of an expression template.
     * 
     * @param a
     */
    template <class REAL_T, class EXPR>
    class Floor;

}

namespace std {

    /**
     * Override for the floor function in namespace std.
     * 
     * @param expr
     * @return 
     */
    template<class REAL_T, class EXPR>
    inline const atl::Floor<REAL_T, EXPR> floor(const atl::ExpressionBase<REAL_T, EXPR>& expr);
}

namespace atl {

    /**
     * Expression template for handling the floor of an expression template.
     * 
     * @param a
     */
    template <class REAL_T, class EXPR>
    class Floor : public ExpressionBase<REAL_T, Floor<REAL_T, EXPR> > {
    public:
        typedef REAL_T BASE_TYPE;

        Floor(const ExpressionBase<REAL_T, EXPR>& a)
        : expr_m(a.Cast()) {
        }

        inline const REAL_T GetValue() const {
            return std::floor(expr_m.GetValue());
        }

        inline void VariableCount(uint32_t& count) const {
            expr_m.VariableCount(count);
        }


        inline void PushIds(IDSet<atl::VariableInfo<REAL_T>* >& ids)const {
            expr_m.PushIds(ids);
        }

        inline REAL_T EvaluateDerivative(uint32_t id) const {
            return (expr_m.EvaluateDerivative(id) * this->GetValue());
        }

        inline REAL_T EvaluateDerivative(uint32_t a, uint32_t b) const {
            return (expr_m.EvaluateDerivative(a, b) * this->GetValue());
        }

    private:
        const EXPR& expr_m;
    } __attribute__((packed));

    template<class REAL_T, class EXPR>
    inline const atl::Floor<REAL_T, EXPR> floor(const atl::ExpressionBase<REAL_T, EXPR>& expr) {

        return atl::Floor<REAL_T, EXPR > (expr.Cast());
    }

}

namespace std {

    /**
     * Override for the floor function in namespace std.
     * 
     * @param expr
     * @return 
     */
    template<class REAL_T, class EXPR>
    inline const atl::Floor<REAL_T, EXPR> floor(const atl::ExpressionBase<REAL_T, EXPR>& expr) {

        return atl::Floor<REAL_T, EXPR > (expr.Cast());
    }
}

#endif	/* FLOOR_HPP */

