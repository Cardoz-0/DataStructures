#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include "linked_stack.hpp"
#include "region_counter.hpp"

namespace xml {
    bool validate(const std::string& contents) {
        structures::LinkedStack<std::string> tags;

        size_t i = 0u;

        while (i < contents.length())
        {
            // Calcula o íncio e final da próxima tag do arquivo
            size_t start_position = contents.find('<', i);
            size_t end_position = contents.find('>', start_position);

            // Caso o find do início falhe, chegamos ao final do arquivo
            if (start_position == std::string::npos) break;

            // Caso a posição do final falhe, temos um erro no arquivo
            if (end_position == std::string::npos) return false;
            
            // Utiliza substring para buscar a tag completa
            std::string tag = contents.substr(start_position, end_position + 1 - start_position);
            
            // Incrementa a posição de busca inicial para a posição seguinte ao final da tag atual
            i = end_position + 1;

            // Caso seja uma tag de abertura, insere na pilha com uma / no início
            // que será utilizada depois para comparação
            if (tag[1] != '/') {
                tags.push(tag.insert(1, "/"));
            } else {
                // Se tiver uma tag de fechamento com a pilha vazia
                // significa que não havia uma tag de abertura, arquivo inválido
                if (tags.empty()) return false;
                // Se a tag de fechamento for igual ao topo da pilha, desempilha o topo
                else if(tags.top() == tag) tags.pop();
                // Do contrário, erro no arquivo
                else return false;  
            }
        }
        
        return tags.empty();
    }

    std::string get_tag(
        const std::string& source, 
        const std::string& open_tag, 
		const std::string& close_tag, 
        size_t& start_index
    )
    {		
        size_t start_position = source.find(open_tag, start_index);
        size_t end_position = source.find(close_tag, start_position);
                
        start_position += open_tag.length();

        std::string tag_contents = source.substr(start_position, end_position - start_position);
        
        return tag_contents;
    }

    std::string get_value(
        const std::string& source, 
        const std::string& open_tag, 
        const std::string& close_tag
    )
    {
        std::size_t pos{0};

        return get_tag(source, open_tag, close_tag, pos);
    }
} // namespace xml

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    std::ifstream xml_file;
    
    xml_file.open(xmlfilename);
    if (not xml_file.is_open()) {
        std::cout << "error\n";
        return -1;
    }
    
    std::stringstream stream;
	stream << xml_file.rdbuf();
	std::string contents = stream.str();

    xml_file.close();
    
      if (not xml::validate(contents)) {
        std::cout << "error\n";
        return -1;
    }
    size_t i = {0};
    
    while (i < contents.length())
    {
        // Busca a tag completa da próxima imagem dentro do arquivo
        std::string open_tag = "<img>";
        std::string close_tag = "</img>";
        std::string image = xml::get_tag(contents, open_tag, close_tag, i);

        i += image.length() + close_tag.length();
        
        // Sai do laço caso tenha chegado ao final das imagens
        if (i > contents.length()) break;
	
        // Utiliza a função get_value pra buscar o conteúdo de cada atributo da imagem
        std::string data = xml::get_value(image, "<data>", "</data>");
        const std::string name = xml::get_value(image, "<name>", "</name>");
        const int width = std::stoi(xml::get_value(image, "<width>", "</width>"));
        const int height = std::stoi(xml::get_value(image, "<height>", "</height>"));

        // Caso seja uma imagem inválida (com alguma das dimensões menores ou iguais a 0)
        // retorna -1 como sinal de erro.
        if (height <= 0|| width <= 0) return -1;

        // Remove \n da string data
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

        std::vector<std::vector<bool>> matrix = region_counter::create_matrix(data, width, height);

        int regions = region_counter::connectivity_counter(matrix);
		std::cout << name << ' ' << regions << std::endl;
    }

    
    

    return 0;
}




