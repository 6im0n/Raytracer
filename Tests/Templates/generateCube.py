import random

def generate_config(x, y, z, s1, s2, s3):
    config = '  {{\n    type = "parallelepiped";\n    position = [{:.2f}, {:.2f}, {:.2f}];\n    size = [{:.2f}, {:.2f}, {:.2f}];\n    material :\n    {{\n      type = "matte";\n      color = [100, 150, 100];\n      texture_is_enabled = false;\n      texture_path = "none";\n    }};\n    transformations = ();\n}}'.format(x, y, z, s1, s2, s3)
    return config

def update_values():
    boxes_per_side = 20
    configs = []

    for i in range(boxes_per_side):
        for j in range(boxes_per_side):
            w = 100.0
            x0 = -1000.0 + i * w
            z0 = -1000.0 + j * w
            y0 = 0.0
            x1 = x0 + w
            s2 = random.uniform(1, 101)
            z1 = z0 + w

            config = generate_config(x0, y0, z0, x1, s2, z1)
            configs.append(config)

    return configs

# Example usage
updated_configs = update_values()
for idx, config in enumerate(updated_configs):
    print(config, end="")
    print(",")
