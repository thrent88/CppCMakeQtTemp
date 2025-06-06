# 对象ID生成器

import os
import math
import argparse
import re


def toScreamingSnake(name: str) -> str:
    # 0. 去除前后空白
    name = name.strip()

    # 1. 替换 - 为 _（处理 kebab-case）
    name = name.replace('-', '_')

    # 2. 移除非 ASCII 字符（可选：保留英文、数字和下划线）
    name = re.sub(r'[^\w]', '', name)

    # 3. 判断是否有前缀（如 kMainWindow → 拆成 k + MainWindow）
    prefix_match = re.match(r'^([a-zA-Z])([A-Z].*)$', name)
    if prefix_match:
        prefix, rest = prefix_match.groups()
    else:
        prefix, rest = '', name

    # 4. 将 camelCase / PascalCase 转为 snake_case
    snake = re.sub(r'([a-z0-9])([A-Z])', r'\1_\2', rest)  # camelCase
    snake = re.sub(r'([A-Z]+)([A-Z][a-z])', r'\1_\2', snake)  # HTMLParser

    # 5. 组合前缀
    if prefix:
        snake = f"{prefix}_{snake}"

    # 6. 转大写
    return snake.upper()


def getIDFileHeader() -> str:
    return """// Generated by GeneratorObjectID.py\n// Do not edit!\n\n"""


# 创建文件夹
def createDir(path):
    if not os.path.exists(path):
        os.makedirs(path)


def getAllCppFiles(path) -> list:
    files = []
    for root, dirs, fileNames in os.walk(path):
        for fileName in fileNames:
            if fileName.endswith(".cpp"):
                files.append(os.path.join(root, fileName))
    return files


def getAllRegisterObjId(cpp_file) -> list:
    # 获取宏函数REGISTER_OBJECT("id", obj);中的ID
    pattern = r'REGISTER_OBJECT\("([^"]+)",\s*[^)]+\);'
    with open(cpp_file, "r", encoding="utf-8") as f:
        lines = f.readlines()
        res = []
        for line in lines:
            ids = re.findall(pattern, line)
            if len(ids) > 0:
                res.append(ids[0])

    return res


if __name__ == '__main__':
    print("Launch GeneratorObjectID.py")

    parser = argparse.ArgumentParser(description='Generate ObjectID.h')
    parser.add_argument('--path', type=str, help='输入')
    parser.add_argument('--out', type=str, help='输出')
    args = parser.parse_args()
    out_path = args.out
    src_path = args.path  # 获取要解析的文件夹

    createDir(out_path)

    cpp_files = getAllCppFiles(src_path)

    print("Start Generate ObjectID.h")

    # 创建文件ObjectIDs.h
    with open(out_path + "/ObjectIDs.h", "w") as f:
        f.write(getIDFileHeader())
        f.write("#ifndef OBJECT_IDS_H__\n#define OBJECT_IDS_H__\n\n")

        f.write("namespace store {\n")
        f.write("    class ObjectID {\n")
        f.write("    public:\n")

        f.write("    // Object ID\n")

        for cpp_file in cpp_files:
            ids = getAllRegisterObjId(cpp_file)
            for index in range(len(ids)):
                id = ids[index]
                # 将ID转换成下划线大写
                idsScream = toScreamingSnake(id)
                f.write("        static constexpr char {}[] = \"{}\";\n".format(idsScream, id))
                # 打印进度
                print("[{}%]: Generate '{}'".format((index + 1) / len(ids) * 100, id))

        f.write("    };\n")
        f.write("}\n\n")

        f.write("#endif // OBJECT_IDS_H__\n")

    pass
