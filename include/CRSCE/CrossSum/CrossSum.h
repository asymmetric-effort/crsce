/**
 * @file include/CRSCE/CrossSum.h
 * @brief Declare the pure virtual CrossSum parent class for LSM, VSM,
 *        DSM and XSM.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <vector>

class CrossSum {
public:
    /**
     * @name default constructor
     * @brief initialize a cross sum matrix with constants s and b.
     */
    explicit CrossSum()=default;
    explicit CrossSum(const CrossSum &) = delete;
    explicit CrossSum(CrossSum &&) noexcept = delete;
    CrossSum &operator=(const CrossSum &) = delete;
    CrossSum &operator=(CrossSum &&) noexcept = delete;

    /**
     * @name destructor
     * @brief default destructor
     */
    virtual ~CrossSum(){
        data.clear();
    }

    /**
     * @name get
     * @brief return a given cross sum value
     * @param r row index
     * @param c column index
     * @return CrossSumValue
     */
    [[nodiscard]] virtual CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const;

    /**
     * @name set
     * @brief set a given cross sum value
     * @param r row index
     * @param c column index
     * @param value CrossSumValue
     */
    virtual auto set(CrossSumIndex r, CrossSumIndex c, const CrossSumValue &value) -> void;

    /**
     * @name increment
     * @brief increment the element at (r,c)
     * @param r row index
     * @param c column index
     */
    virtual void increment(CrossSumIndex r, CrossSumIndex c);

    /**
     * @name serialize
     * @brief serialize the cross sum state to the output stream
     * @param os output file stream
     */
    void serialize(std::ostream &os) const;

    /**
     * @name deserialize
     * @brief deserialize the input stream into the cross sum state
     * @param is input file stream
     */
    void deserialize(std::istream &is) const;

protected:
    /**
     * @name storage
     * @brief return a vector of CrossSumValue (underlying storage)
     * @return std::vector<CrossSumValue>
     */
    virtual std::vector<CrossSumValue> &storage() {
        return data;
    }

    /**
     * @name storage
     * @brief return a vector of CrossSumValue (underlying storage)
     * @return std::vector<CrossSumValue>
     */
    [[nodiscard]] virtual const std::vector<CrossSumValue> &storage() const {
        return data;
    }

private:

    /**
     * @name data
     * @brief Initialize vector with 'size' (s) elements all zeroed.
     */
    // cppcheck-suppress unusedStructMember
    mutable std::vector<CrossSumValue> data = std::vector<CrossSumValue>(s);
};
