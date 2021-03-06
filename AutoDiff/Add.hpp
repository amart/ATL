/* 
 * File:   Addition.hpp
 * Author: matthewsupernaw
 *
 * Created on June 18, 2014, 11:36 AM
 */

#ifndef ET4AD_ADD_HPP
#define	ET4AD_ADD_HPP

#include "Expression.hpp"


namespace atl {

    template <class REAL_T, class LHS, class RHS>
    struct Add : public ExpressionBase<REAL_T, Add<REAL_T, LHS, RHS> > {
        typedef REAL_T BASE_TYPE;

        Add(const ExpressionBase<REAL_T, LHS>& lhs, const ExpressionBase<REAL_T, RHS>& rhs)
        : lhs_m(lhs.Cast()), rhs_m(rhs.Cast()), value_m(lhs_m.GetValue() + rhs_m.GetValue()) {

            //            std::cout<<lhs.GetId()<<" - "<<rhs.GetId()<<"\n";
        }

        inline const REAL_T GetValue() const {
            return value_m;
        }

        inline void VariableCount(uint32_t& count) const {
            lhs_m.VariableCount(count);
            rhs_m.VariableCount(count);
        }

        operator REAL_T() {
            return this->GetValue();
        }

        operator REAL_T()const {
            return this->GetValue();
        }

        inline void PushIds(IDSet<atl::VariableInfo<REAL_T>* >& ids)const {
            lhs_m.PushIds(ids);
            rhs_m.PushIds(ids);
        }

        inline REAL_T EvaluateDerivative(uint32_t id) const {
            return lhs_m.EvaluateDerivative(id) + rhs_m.EvaluateDerivative(id);
        }

        inline REAL_T EvaluateDerivative(uint32_t a, uint32_t b) const {
            return lhs_m.EvaluateDerivative(a, b) + rhs_m.EvaluateDerivative(a, b);
        }



        const LHS& lhs_m;
        const RHS& rhs_m;
        REAL_T value_m;
    } __attribute__((packed));

    /**
     * Operator for addition of two expression templates.
     * @param a
     * @param b
     * @return 
     */
    template <class REAL_T, class LHS, class RHS>
    inline Add<REAL_T, LHS, RHS> operator+(const ExpressionBase<REAL_T, LHS>& a,
            const ExpressionBase<REAL_T, RHS>& b) {
        return Add<REAL_T, LHS, RHS > (a.Cast(), b.Cast());
    }

    template <class REAL_T, class LHS>
    struct AddConstant : public ExpressionBase<REAL_T, AddConstant<REAL_T, LHS> > {
        typedef REAL_T BASE_TYPE;

        AddConstant(const ExpressionBase<REAL_T, LHS>& lhs, const REAL_T & rhs)
        : lhs_m(lhs.Cast()), rhs_m(rhs) {


        }

        inline const REAL_T GetValue() const {
            return lhs_m.GetValue() + rhs_m;
        }

        inline void VariableCount(uint32_t& count) const {
            lhs_m.VariableCount(count);
        }

        inline void PushStackEntry(Entry& entry, REAL_T coefficient = 1.00000e+0) const {
            lhs_m.PushStackEntry(entry, coefficient);
        }

        inline void PushIds(IDSet<atl::VariableInfo<REAL_T>* >& ids)const {
            lhs_m.PushIds(ids);
        }

        inline REAL_T EvaluateDerivative(uint32_t id) const {
            return lhs_m.EvaluateDerivative(id);
        }

        inline REAL_T EvaluateDerivative(uint32_t a, uint32_t b) const {
            return lhs_m.EvaluateDerivative(a, b);
        }

        const LHS& lhs_m;
        REAL_T rhs_m;
        //        const REAL_T value_m;
    } __attribute__((packed));

    /**
     * Operator for adding a expression templates to a constant .
     * @param lhs
     * @param rhs
     * @return 
     */
    template <class LHS, class REAL_T>
    inline const AddConstant<REAL_T, LHS> operator+(const ExpressionBase<REAL_T, LHS>& lhs,
            const REAL_T& rhs) {
        return AddConstant<REAL_T, LHS > (lhs.Cast(), rhs);
    }

    template <class REAL_T, class RHS>
    struct ConstantAdd : public ExpressionBase<REAL_T, ConstantAdd<REAL_T, RHS> > {
        typedef REAL_T BASE_TYPE;

        ConstantAdd(const REAL_T& lhs, const ExpressionBase<REAL_T, RHS>& rhs)
        : lhs_m(lhs), rhs_m(rhs.Cast()), value_m(lhs_m + rhs_m.GetValue()) {


        }

        inline const REAL_T GetValue() const {
            return value_m;
        }

        inline void VariableCount(uint32_t& count) const {
            rhs_m.VariableCount(count);
        }

        inline void PushStackEntry(Entry& entry, REAL_T coefficient = 1.00000e+0) const {
            rhs_m.PushStackEntry(entry, coefficient);
        }

        inline void PushIds(IDSet<atl::VariableInfo<REAL_T>* >& ids)const {
            rhs_m.PushIds(ids);
        }

        inline REAL_T EvaluateDerivative(uint32_t id) const {
            return rhs_m.EvaluateDerivative(id);
        }

        inline REAL_T EvaluateDerivative(uint32_t a, uint32_t b) const {
            return rhs_m.EvaluateDerivative(a, b);
        }

        REAL_T lhs_m;
        const RHS& rhs_m;
        REAL_T value_m;
    } __attribute__((packed));

    /**
     * Operator for adding a constant value to a expression templates.
     * @param lhs
     * @param rhs
     * @return 
     */
    template <class REAL_T, class RHS >
    inline const ConstantAdd< REAL_T, RHS > operator+(const REAL_T& lhs,
            const ExpressionBase<REAL_T, RHS> &rhs) {
        return ConstantAdd<REAL_T, RHS > (lhs, rhs.Cast());
    }

}




#endif	/* ADDITION_HPP */

