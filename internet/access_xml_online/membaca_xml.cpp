#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>

void parseXML(const std::string& xmlData) {
    xmlDocPtr doc = xmlReadMemory(xmlData.c_str(), xmlData.size(), "https://data.bmkg.go.id/DataMKG/MEWS/DigitalForecast/DigitalForecast-DIYogyakarta.xml", nullptr, 0);

    if (doc == nullptr) {
        std::cerr << "Failed to parse XML data." << std::endl;
        return;
    }

    xmlNodePtr rootNode = xmlDocGetRootElement(doc);

    for (xmlNodePtr node = rootNode->children; node != nullptr; node = node->next) {
        if (node->type == XML_ELEMENT_NODE && xmlStrEqual(node->name, BAD_CAST "forecast")) {
            xmlNodePtr issueNode = node->children;

            while (issueNode != nullptr) {
                if (issueNode->type == XML_ELEMENT_NODE) {
                    std::string nodeName(reinterpret_cast<const char*>(issueNode->name));

                    if (nodeName == "timestamp") {
                        std::cout << "Timestamp: " << xmlNodeGetContent(issueNode) << std::endl;
                    } else if (nodeName == "area") {
                        std::string areaName;
                        for (xmlNodePtr areaChildNode = issueNode->children; areaChildNode != nullptr;
                             areaChildNode = areaChildNode->next) {
                            if (areaChildNode->type == XML_ELEMENT_NODE && xmlStrEqual(areaChildNode->name, BAD_CAST "name")) {
                                areaName = reinterpret_cast<const char*>(xmlNodeGetContent(areaChildNode));
                                break;
                            }
                        }
                        std::cout << "Area Name: " << areaName << std::endl;
                    }

                    // Add more conditions as needed to extract other information
                }

                issueNode = issueNode->next;
            }
        }
    }

    xmlFreeDoc(doc);
}

int main() {
    std::string xmlData = R"(
        <!-- Your XML data goes here -->
    )";

    parseXML(xmlData);

    return 0;
}

