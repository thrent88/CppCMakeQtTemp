# 表单生成器
import argparse
import os
import json

def load_form_config(json_path):
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
            print("JSON 加载成功")
            return data
    except FileNotFoundError:
        print(f"文件未找到: {json_path}")
    except json.JSONDecodeError as e:
        print(f"JSON 解析错误: {e}")
    return None

# 创建文件夹
def createDir(path):
    if not os.path.exists(path):
        os.makedirs(path)

def getAllCppFiles(path) -> list:
    files = []
    for root, dirs, fileNames in os.walk(path):
        for fileName in fileNames:
            if fileName.endswith(".json"):
                files.append(os.path.join(root, fileName))
    return files

if __name__ == '__main__':
    print("Launch GeneratorForm.py")

    parser = argparse.ArgumentParser(description='Generate Form')
    parser.add_argument('--path', type=str, help='输入')
    parser.add_argument('--out', type=str, help='输出')
    args = parser.parse_args()


    out_path = args.out
    src_path = args.path  # 获取要解析的文件夹

    createDir(out_path + "/include/form")

    json_files = getAllCppFiles(src_path)

    json_objs = []
    for json_file in json_files:
        json_obj = load_form_config(json_file)
        json_objs.append(json_obj)

    print(json_objs)

