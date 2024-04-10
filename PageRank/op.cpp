/*
    KARAN DEO BURNWAL
    2022EE11342
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <chrono>

class SparseMatrix
{
public:
    bool all_same = false;
    double all_same_val = 0;
    int rows;
    int cols;
    std::unordered_map<int, std::unordered_map<int, double>> data;

    SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {}

    void set_value(int row, int col, double value)
    {
        if (value != 0)
        {
            data[row][col] = value;
        }
        else if (data.find(row) != data.end() && data[row].find(col) != data[row].end())
        {
            data[row].erase(col);
        }
    }

    double get_value(int row, int col) const
    {
        if (all_same)
        {
            return all_same_val;
        }

        auto row_iter = data.find(row);
        if (row_iter != data.end())
        {
            auto col_iter = row_iter->second.find(col);
            if (col_iter != row_iter->second.end())
            {
                return col_iter->second;
            }
        }

        return 0;
    }

    SparseMatrix add(const SparseMatrix &other) const
    {
        SparseMatrix result(rows, cols);

        if (all_same)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    result.set_value(i, j, all_same_val + other.get_value(i, j));
                }
            }

            return result;
        }

        if (other.all_same)
        {
            double same_val = other.all_same_val;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    result.set_value(i, j, get_value(i, j) + same_val);
                }
            }
        }

        for (const auto &[row, row_data] : data)
        {
            for (const auto &[col, value] : row_data)
            {
                double sum = value + other.get_value(row, col);
                if (sum != 0)
                {
                    result.set_value(row, col, sum);
                }
            }
        }

        for (const auto &[row, row_data] : other.data)
        {
            for (const auto &[col, value] : row_data)
            {
                if (result.get_value(row, col) == 0)
                {
                    result.set_value(row, col, value);
                }
            }
        }

        return result;
    }

    SparseMatrix sub(const SparseMatrix &other) const
    {
        SparseMatrix result(rows, cols);

        if (all_same)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    result.set_value(i, j, all_same_val - other.get_value(i, j));
                }
            }

            return result;
        }

        if (other.all_same)
        {
            double same_val = other.all_same_val;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    result.set_value(i, j, get_value(i, j) - same_val);
                }
            }
        }

        for (const auto &[row, row_data] : data)
        {
            for (const auto &[col, value] : row_data)
            {
                double diff = value - other.get_value(row, col);
                if (diff != 0)
                {
                    result.set_value(row, col, diff);
                }
            }
        }

        for (const auto &[row, row_data] : other.data)
        {
            for (const auto &[col, value] : row_data)
            {
                if (result.get_value(row, col) == 0)
                {
                    result.set_value(row, col, -1 * value);
                }
            }
        }

        return result;
    }

    SparseMatrix multiply_scalar(double scalar) const
    {
        SparseMatrix result(rows, cols);
        for (const auto &[row, row_data] : data)
        {
            for (const auto &[col, value] : row_data)
            {
                result.set_value(row, col, value * scalar);
            }
        }
        return result;
    }

    SparseMatrix multiply_vector(const SparseMatrix &other) const
    {
        SparseMatrix result(rows, 1);

        if (all_same)
        {
            double prod = 0;
            for (int i = 0; i < rows; i++)
            {
                prod += other.get_value(i, 0);
            }
            prod *= all_same_val;
            result.all_same = true;
            result.all_same_val = prod;

            return result;
        }

        if (other.all_same)
        {
            double same_val = other.all_same_val;

            for (const auto &[row, row_data] : data)
            {
                double result_value = 0;
                for (const auto &[col, value] : row_data)
                {
                    result_value += value;
                }
                if (result_value != 0)
                {
                    result.data[row][0] = result_value * same_val;
                }
            }
            return result;
        }

        for (const auto &[row, row_data] : data)
        {
            double result_value = 0;
            for (const auto &[col, value] : row_data)
            {
                result_value += value * other.get_value(col, 0);
            }
            if (result_value != 0)
            {
                result.data[row][0] = result_value;
            }
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const SparseMatrix &matrix);
};

std::ostream &operator<<(std::ostream &os, const SparseMatrix &matrix)
{
    for (int row = 0; row < matrix.rows; ++row)
    {
        for (int col = 0; col < matrix.cols; ++col)
        {
            double value = matrix.get_value(row, col);
            if (value != 0)
            {
                os << value << " ";
            }
            else
            {
                os << "0  ";
            }
        }
        os << "\n";
    }
    return os;
}

SparseMatrix compute_importance_vector(const std::unordered_map<int, std::vector<int>> &links, double tolerance = 1e-5)
{

    int num_pages = 0;

    for (const auto &pair : links)
    {
        int p = pair.first;
        if (p > num_pages)
        {
            num_pages = p;
        }
        for (int q : pair.second)
        {
            if (q > num_pages)
            {
                num_pages = q;
            }
        }
    }

    num_pages++;

    // Hyperlink matrix H
    SparseMatrix H(num_pages, num_pages);

    for (const auto &[row, row_data] : links)
    {
        double val = row_data.size();
        val = 1 / val;
        for (int col : row_data)
        {
            H.set_value(col, row, val * 0.85);
        }
    }

    double inv_val = (0.85 / num_pages);
    for (int i = 0; i < num_pages; ++i)
    {
        if (links.find(i) == links.end())
        {
            for (int j = 0; j < num_pages; ++j)
            {
                H.set_value(j, i, inv_val);
            }
        }
    }

    // Importance vector I
    SparseMatrix I(num_pages, 1);
    I.all_same = true;
    I.all_same_val = double(1.0/num_pages);






    // ** The Google matrix G ** //

    // Ones matrix
    double identity_val = (0.15 / num_pages);
    SparseMatrix Identity(num_pages, num_pages);
    Identity.all_same = true;
    Identity.all_same_val = identity_val;


    while (true)
    {

        auto start = std::chrono::steady_clock::now();

        SparseMatrix I1 = H.multiply_vector(I);
        auto end = std::chrono::steady_clock::now();
        SparseMatrix I2 = Identity.multiply_vector(I);
        SparseMatrix I_new = I1.add(I2);
        
        // std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        double norm = 0;
        for (const auto &row_data : I_new.data)
        {
            for (const auto &col_value : row_data.second)
            {
                norm += std::abs(col_value.second);
            }
        }

        for (auto [row, row_data] : I_new.data)
        {
            for (auto [col, value] : row_data)
            {
                I_new.set_value(row, col, value / norm);
            }
        }

        SparseMatrix I_sub = I_new.sub(I);

        norm = 0;
        for (const auto &[row, row_data] : I_sub.data)
        {
            for (const auto &[col, col_value] : row_data)
            {
                norm += col_value * col_value;
            }
        }

        norm = sqrt(norm);

        if (norm < tolerance)
        {
            break;
        }

        I = I_new;
    }

    return I;
}

int main()
{

    // Input
    std::unordered_map<int, std::vector<int>> links;
    int p, q;

    while (std::cin >> p >> q)
    {
        links[p].push_back(q);
    }

    auto start = std::chrono::steady_clock::now();
    //  Calculation
    SparseMatrix importance_vector = compute_importance_vector(links);
    auto end = std::chrono::steady_clock::now();

    // Output
    // for (int i = 0; i < importance_vector.rows; ++i)
    // {
    //     std::cout << i << " = " << importance_vector.get_value(i, 0) << std::endl;
    // }

    std::cout << "s = 1.0" << std::endl;

    double elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << std::endl << "Time: " << elapsed_seconds / 1000 << " s" << std::endl;

    return 0;
}
