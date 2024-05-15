import random

def generate_config(x, y, z):
    config = '  {{\n    type = "sphere";\n    position = [{:.2f}, {:.2f}, {:.2f}];\n    radius = 10.0;\n    material :\n    {{\n      type = "matte";\n      color = [186, 186, 186];\n      texture_is_enabled = false;\n      texture_path = "none";\n    }};\n    transformations = ();\n}}'.format(x, y, z)
    return config

def update_values():
    boxes_per_side = 1000
    configs = []

    for i in range(boxes_per_side):
        x0 = random.uniform(0, 165)
        z0 = random.uniform(150, 315)
        y0 = random.uniform(150, 315)

        config = generate_config(x0, y0, z0)
        configs.append(config)

    return configs

# Example usage
updated_configs = update_values()
for idx, config in enumerate(updated_configs):
    print(config, end="")
    print(",")
