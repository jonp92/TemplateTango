#ifndef TEMPLATETANGO_H
#define TEMPLATETANGO_H

#include <Arduino.h>
#include <map>
#include <string>
#include <regex>
#include <sstream>
#include <cmath>

using namespace std;

/**
 * @class TemplateTango
 * @brief A class for template processing, supporting variable replacement and basic expression evaluation.
 */
class TemplateTango {
public:
    /**
     * @brief Render the template string with the provided variables.
     * @param templateStr The template string containing placeholders for variables.
     * @param variables A map of variable names and their corresponding values.
     * @return A string with variables replaced by their corresponding values.
     */
    static string render(const string& templateStr, const map<string, string>& variables) {
        string result = templateStr;
        regex varRegex("\\{\\{(.*?)\\}\\}");
        smatch matches;
        while (regex_search(result, matches, varRegex)) {
            string varExpression = matches[1].str();
            // Evaluate the expression
            string evaluated = evaluateExpression(varExpression, variables);
            result.replace(matches.position(0), matches.length(0), evaluated);
        }
        return result;
    }

private:
    /**
     * @brief Evaluate an expression by replacing variables and computing the result.
     * @param expression The expression to evaluate.
     * @param variables A map of variable names and their corresponding values.
     * @return The evaluated result as a string.
     */
    static string evaluateExpression(const string& expression, const map<string, string>& variables) {
        // Replace variables with their values
        string expr = expression;
        for (const auto& var : variables) {
            regex varRegex("\\b" + var.first + "\\b");
            expr = regex_replace(expr, varRegex, var.second);
        }

        // Handle string concatenation with **
        regex concatRegex(R"((\"[^\"]*\")\s*\*\*\s*(\"[^\"]*\"))");
        smatch concatMatch;
        while (regex_search(expr, concatMatch, concatRegex)) {
            string left = concatMatch[1].str();
            string right = concatMatch[2].str();
            left = left.substr(1, left.size() - 2);  // Remove quotes
            right = right.substr(1, right.size() - 2);  // Remove quotes
            string concatenated = "\"" + left + right + "\"";
            expr.replace(concatMatch.position(0), concatMatch.length(0), concatenated);
        }

        // Evaluate arithmetic expressions
        double result = evaluateArithmetic(expr);
        // Remove trailing zeroes and decimal point if not needed
        string resultStr = to_string(result);
        resultStr.erase(resultStr.find_last_not_of('0') + 1, string::npos);
        if (resultStr.back() == '.') {
            resultStr.pop_back();
        }
        return resultStr;
    }

    /**
     * @brief Evaluate a basic arithmetic expression.
     * @param expr The arithmetic expression to evaluate.
     * @return The result of the expression as a double.
     */
    static double evaluateArithmetic(const string& expr) {
        stringstream ss(expr);
        double result = 0.0;
        double term;
        char op = '+';
        while (ss >> term) {
            switch (op) {
                case '+': result += term; break;
                case '-': result -= term; break;
                case '*': result *= term; break;
                case '/': result /= term; break;
                case '%': result = fmod(result, term); break;
            }
            ss >> op;
        }
        return result;
    }
};

#endif // TEMPLATETANGO_H
