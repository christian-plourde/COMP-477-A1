out vec3 color;

uniform vec3 light_color_1;
uniform vec3 light_position_1;
uniform vec3 view_position;

in vec3 fragment_position;
in vec3 normal;
in vec2 tex;

void main()
{
    color = vec3(1,1,1);

    //Ambient light
    float ambient_strength = 0.25f;
    vec3 ambient = ambient_strength * light_color_1;


    //diffuse light
    float diffuse_coeff = 0.75f;
    vec3 light_direction_1 = normalize(light_position_1 - fragment_position);
    float diffuse_strength_1 = max(dot(normalize(normal), light_direction_1), 0.0f);

    vec3 diffuse = diffuse_strength_1*diffuse_coeff*light_color_1;

    //specular light
    float spec_coeff = 1.0f;
    
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_light_direction_1 = reflect(-light_direction_1, normalize(normal));
    float specular_strength_1 = pow(max(dot(reflect_light_direction_1, view_direction), 0.0f), 32);
    vec3 specular = specular_strength_1*spec_coeff*light_color_1;

    color = (specular + ambient + diffuse)*color;
}