#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

class Price {
public:
    std::string productName;
    std::string productType;
    int productCost;
    int componentsCount;
    std::string components[999];

    Price(std::string prodName, std::string prodType, int prodPrice, int compCount, std::string comps[]) {
        productName = std::move(prodName);
        productType = std::move(prodType);
        productCost = prodPrice;
        componentsCount = compCount;

        for (int i = 0; i < compCount; ++i) {
            components[i] = comps[i];
        }
    }

    void updateProductName(std::string &newName) {
        productName = newName;
    }

    void updateProductType(std::string &newType) {
        productType = newType;
    }

    void updateProductCost(int &newCost) {
        productCost = newCost;
    }

    void updateProductComponents(int newComponentsCount, std::string newComponents[999]) {
        for (int i = 0; i < 999; ++i) {
            components[i] = newComponents[i];
        }

        componentsCount = newComponentsCount;
    }
};

std::vector<Price> getNewPriceListFromConsole() {
    std::string prodName;
    std::string prodType;
    int prodPrice;
    int compsCount;

    int n;

    std::cout << "Enter the amount of objects (n) you want to create:";
    std::cin >> n;

    std::cout << "\n";

    std::vector<Price> pricesArray;

    for (int i = 0; i < n; ++i) {
        std::cout << "Input product name:";
        std::cin >> prodName;

        std::cout << "Input product type:";
        std::cin >> prodType;

        std::cout << "Input the price of product:";
        std::cin >> prodPrice;

        std::cout << "Input the amount of components in your products:";
        std::cin >> compsCount;
        std::cout << "Now input them all (g for good component, h for harmful):";

        std::string comps[compsCount];

        for (int c = 0; c < compsCount; ++c) {
            std::cin >> comps[c];
        }

        std::cout << "\n";

        Price newPrice = Price(prodName, prodType, prodPrice, compsCount, comps);

        pricesArray.push_back(newPrice);
    }

    return pricesArray;
}

void coutSpaceNTimes(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << " ";
    }
}

std::vector<Price> getNewPriceListFromFile(const char *filePath) {
    int n;
    std::ifstream in(filePath);

    in >> n;

    std::vector<Price> pricesArray;

    for (int i = 0; i < n; ++i) {
        std::string prodName;
        std::string prodType;
        int prodPrice;
        int compsCount;

        in >> prodName;
        in >> prodType;
        in >> prodPrice;
        in >> compsCount;

        std::string comps[compsCount];

        for (int c = 0; c < compsCount; ++c) {
            in >> comps[c];
        }

        Price newPrice = Price(prodName, prodType, prodPrice, compsCount, comps);

        pricesArray.push_back(newPrice);
    }

    return pricesArray;
}

void addPriceToList(std::vector<Price> &priceList) {
    std::string prodName;
    std::string prodType;
    int prodPrice;
    int compsCount;

    std::cout << "Input product name:";
    std::cin >> prodName;

    std::cout << "Input product type:";
    std::cin >> prodType;

    std::cout << "Input the price of product:";
    std::cin >> prodPrice;

    std::cout << "Input the amount of components in your products:";
    std::cin >> compsCount;
    std::cout << "Now input them all (g for good component, h for harmful):";

    std::string comps[compsCount];

    for (int c = 0; c < compsCount; ++c) {
        std::cin >> comps[c];
    }

    std::cout << "\n";

    Price newPrice = Price(prodName, prodType, prodPrice, compsCount, comps);

    priceList.push_back(newPrice);
}

void deletePriceFromList(std::vector<Price> &priceList, const std::string &priceName) {
    std::vector<Price> newVec = {};

    for (const Price &price : priceList) {
        if (price.productName != priceName) {
            newVec.push_back(price);
        }
    }

    priceList = newVec;
}

void changePriceNameInList(std::vector<Price> &pricesList, std::string &oldName, std::string &newName) {
    for (Price &price : pricesList) {
        if (price.productName == oldName) {
            price.productName = newName;
        }
    }
}

void changePriceTypeInList(std::vector<Price> &pricesList, std::string &priceName, std::string &newType) {
    for (Price &price : pricesList) {
        if (price.productName == priceName) {
            price.updateProductType(newType);
        }
    }
}

void changePriceCostInList(std::vector<Price> &pricesList, std::string &priceName, int newCost) {
    for (Price &price : pricesList) {
        if (price.productName == priceName) {
            price.updateProductCost(newCost);
        }
    }
}

void changePriceComponentsInList(
    std::vector<Price> &priceList,
    std::string &priceName,
    int newComponentsCount,
    std::string newComponents[999]
) {
    for (Price &price : priceList) {
        if (price.productName == priceName) {
            price.updateProductComponents(newComponentsCount, newComponents);
        }
    }
}

int main() {
    int inputMethod;
    std::vector<Price> pricesList;
    int menuInput = 0;

    std::cout << "Choose whether you want to input data from file (1) or console (2):";
    std::cin >> inputMethod;

    std::cout << "\n";

    if (inputMethod == 1) {
        pricesList = getNewPriceListFromFile(R"(C:\Users\Fenek\CLionProjects\lab_4\input.txt)");
    } else if (inputMethod == 2) {
        pricesList = getNewPriceListFromConsole();
    } else {
        std::cout << "\nWrong input!";

        return 0;
    }

    while (menuInput >= 0 && menuInput < 8) {
        switch (menuInput) {
            case 0: {
                break;
            }
            case 1: {
                double averageCost = 0;

                std::sort(
                    pricesList.begin(),
                    pricesList.end(),
                    [](const Price &x, const Price &y) {
                        if (x.productType == y.productType) {
                            return x.productName < y.productName;
                        } else {
                            return x.productType < y.productType;
                        }
                    }
                );

                std::cout << "SORTED ARRAY\n";

                size_t maxNameLength = std::max_element(
                    pricesList.begin(),
                    pricesList.end(),
                    [&](const Price &price, const Price &secondPrice) {
                        return price.productName.size() < secondPrice.productName.size();
                    }
                )[0].productName.size();

                size_t maxTypeLength = std::max_element(
                    pricesList.begin(),
                    pricesList.end(),
                    [&](const Price &price, const Price &secondPrice) {
                        return price.productType.size() < secondPrice.productType.size();
                    }
                )[0].productType.size();

                size_t maxCostLength = std::to_string(
                    std::max_element(
                        pricesList.begin(),
                        pricesList.end(),
                        [&](const Price &price, const Price &secondPrice) {
                            return std::to_string(price.productCost).size() < std::to_string(secondPrice.productCost).size();
                        }
                    )[0].productCost
                ).size() + 1;

                std::cout << "------------------------------------------------------------------\n";
                std::cout << "Name";
                coutSpaceNTimes(maxNameLength - 3);
                std::cout << "| Type";
                coutSpaceNTimes(maxTypeLength - 3);
                std::cout << "| Cost";
                coutSpaceNTimes(maxCostLength - 3);
                std::cout << "| Components\n";
                std::cout << "------------------------------------------------------------------\n";

                for (const Price &price : pricesList) {
                    std::cout << price.productName;
                    coutSpaceNTimes(maxNameLength - price.productName.size());
                    std::cout << " | ";

                    std::cout << price.productType;
                    coutSpaceNTimes(maxTypeLength - price.productType.size());
                    std::cout << " | ";

                    std::cout << price.productCost;
                    coutSpaceNTimes(maxCostLength - std::to_string(price.productCost).size());
                    std::cout << " | ";

                    for (int i = 0; i < price.componentsCount; ++i) {
                        std::cout << price.components[i] << " ";
                    }

                    std::cout << "\n";

                    averageCost += price.productCost;
                }

                std::cout << "------------------------------------------------------------------\n";

                Price minHarmfulComponentsPrice = std::min_element(
                    pricesList.begin(),
                    pricesList.end(),
                    [](const Price &x, const Price &y) {
                        return std::count(x.components, x.components + x.componentsCount, "h")
                            < std::count(y.components, y.components + y.componentsCount, "h");
                    }
                )[0];

                int minHarmfulComponentsCount = (int) std::count(
                    minHarmfulComponentsPrice.components,
                    minHarmfulComponentsPrice.components + minHarmfulComponentsPrice.componentsCount,
                    "h"
                );

                averageCost /= (double) pricesList.size();

                std::cout << "\nAVERAGE PRICE: " << averageCost << "\n\n";
                std::cout << "PRODUCTS WITH MINIMAL HARMFUL COMPONENTS COUNT" << " (" << minHarmfulComponentsCount << ") \n";
                std::cout << "------------------------------------------------------------------\n";
                std::cout << "Name";
                coutSpaceNTimes(maxNameLength - 3);
                std::cout << "| Type";
                coutSpaceNTimes(maxTypeLength - 3);
                std::cout << "| Cost";
                coutSpaceNTimes(maxCostLength - 3);
                std::cout << "| Components\n";
                std::cout << "------------------------------------------------------------------\n";

                for (const Price &price : pricesList) {
                    int priceHarmfulComponentsCount = (int) std::count(
                        price.components,
                        price.components + price.componentsCount,
                        "h"
                    );

                    if (priceHarmfulComponentsCount == minHarmfulComponentsCount) {
                        std::cout << price.productName;
                        coutSpaceNTimes(maxNameLength - price.productName.size());
                        std::cout << " | ";

                        std::cout << price.productType;
                        coutSpaceNTimes(maxTypeLength - price.productType.size());
                        std::cout << " | ";

                        std::cout << price.productCost;
                        coutSpaceNTimes(maxCostLength - std::to_string(price.productCost).size());
                        std::cout << " | ";

                        for (int i = 0; i < price.componentsCount; ++i) {
                            std::cout << price.components[i] << " ";
                        }

                        std::cout << "\n";
                    }
                }

                std::cout << "------------------------------------------------------------------\n";

                break;
            }

            case 2: {
                addPriceToList(pricesList);

                break;
            }

            case 3: {
                std::string productToDelete;

                std::cout << "Write the name of the product you want to delete:";
                std::cin >> productToDelete;

                deletePriceFromList(pricesList, productToDelete);

                std::cout << "\n\n";

                break;
            }

            case 4: {
                std::string productToChangeName;
                std::string newProductName;

                std::cout << "Write the name of the product which you want to change name for and its new name:";
                std::cin >> productToChangeName >> newProductName;
                std::cout << "\n";

                changePriceNameInList(pricesList, productToChangeName, newProductName);

                break;
            }

            case 5: {
                std::string productToChangeName;
                std::string newProductType;

                std::cout << "Write the name of the product which you want to change type for and then write its new type:";
                std::cin >> productToChangeName >> newProductType;
                std::cout << "\n";

                changePriceTypeInList(pricesList, productToChangeName, newProductType);

                break;
            }

            case 6: {
                std::string productToChangeName;
                int newProductCost;

                std::cout << "Write the name of the product which you want to change cost for and then write its new cost:";
                std::cin >> productToChangeName >> newProductCost;
                std::cout << "\n";

                changePriceCostInList(pricesList, productToChangeName, newProductCost);

                break;
            }

            case 7: {
                std::string productToChangeName;
                int newComponentsCount;
                std::string newComponents[999];

                std::cout << "Write the name of the product which you want to change components:";
                std::cin >> productToChangeName;
                std::cout << "\nWrite new components list length:";
                std::cin >> newComponentsCount;
                std::cout << "\nNow write the components themselves (g for good and h for harmful):";

                for (int i = 0; i < newComponentsCount; ++i) {
                    std::cin >> newComponents[i];
                }

                changePriceComponentsInList(pricesList, productToChangeName, newComponentsCount, newComponents);

                break;
            }

            default: {
                return 0;
            }
        }

        std::cout << "\nMENU | Choose one of the following options\n";
        std::cout << "1. Show prices\n";
        std::cout << "2. Add new price\n";
        std::cout << "3. Delete price\n";
        std::cout << "4. Change price name\n";
        std::cout << "5. Change price type\n";
        std::cout << "6. Change price cost\n";
        std::cout << "7. Change price components\n";

        std::cin >> menuInput;

        std::cout << "=========================================================\n\n\n";
    }
}
