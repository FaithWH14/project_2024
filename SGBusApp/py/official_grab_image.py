import uiautomation as auto
from PIL import ImageGrab
import time
from sql_query import get_bus_stations

def open_edge():
    start_btn = auto.ButtonControl(Name="Start", searchDepth=6)
    start_btn.Click()

    search_btn = auto.ButtonControl(Name="Search for apps, settings, and documents", searchDepth=3)
    search_btn.Click()
    search_edit = auto.EditControl(Name="Search box", searchDepth=2)
    search_edit.SetFocus()
    search_edit.SendKeys("Microsoft Edge")
    auto.SendKeys("{ENTER}")

    edge_wnd = auto.WindowControl(ClassName="Chrome_WidgetWin_1", searchDepth=2)
    edge_wnd.Maximize()

def open_google_map():
    url = "https://www.google.com/maps"

    search_box = auto.EditControl(Name="Address and search bar", searchDepth=10)
    search_box.Click()
    search_box.SendKeys(f"{url}")
    search_box.SendKeys("{ENTER}")

def search_google_map_place(place):

    map_search = auto.EditControl(Name="Search Google Maps", searchDepth=25)
    map_search.Click()

    place += " bus station"
    map_search.SendKeys(place)
    map_search.SendKeys("{ENTER}")

def click_on_place_image():
    # image_ui = auto.ImageControl(ClassName="aFsglc widget-scene-canvas", searchDepth=30)
    name = "To get missing image descriptions, open the context menu."
    image_ui = auto.ImageControl(Name=name, searchDepth=30)

    image_ui.Click()
    time.sleep(1)

def capture_images(place, num=1):
    for i in range(num):
        left, top, width, height = 663, 199, 1148, 738
        right, bottom = 1811, 937
        screenshot = ImageGrab.grab()
        cropped_sreenshot = screenshot.crop((left, top, right, bottom))
        cropped_sreenshot.save(f"images/{place.replace(' ', '_')}_{i+1}.png", format="png")

        next_btn = auto.ButtonControl(Name="Next", ClassName="eU5Rrb L6Bbsd AnCkCf", searchDepth=25)
        if not next_btn.Exists():
            close_btn = auto.ButtonControl(Name="Close", ClassName="b3vVFf", searchDepth=30)
            close_btn.Click()
            print("THE IMAGES NOT EXISTS, SKIP THIS")
            return
        next_btn.Click()
        time.sleep(0.5)

def next_bus_station_search(place):
    search_box = auto.EditControl(ClassName="searchboxinput xiQnY", searchDepth=25)
    search_box.Click()
    search_box.SendKeys("{Ctrl}a{Delete}")
    search_box.SendKeys(place + " bus station")
    search_box.SendKeys("{ENTER}")

def second_image_click():
    target = auto.GroupControl(ClassName="m6QErb WNBkOb ", searchDepth=25)
    image_click = target.ImageControl(Name="")
    if image_click.Exists():
        image_click.Click()
        return
    else:
        target = auto.GroupControl(ClassName="Nv2PK Q2HXcd THOPZb ", searchDepth=30)

    if not target.Exists():
        print("The target is not exists, try next approach")
        target = auto.GroupControl(ClassName="Nv2PK THOPZb CpccDe ", searchDepth=30)
        if not target.Exists():
            raise Exception("The third approach to find target not work")
    hyperlink = target.HyperlinkControl(ClassName="hfpxzc")
    if not hyperlink.Exists():
        raise Exception("hyperlink is not exists, PLEASE CHECK!")

    hyperlink.Click()

    img_click = auto.ButtonControl(ClassName="aoRNLd kn2E5e NMjTrf lvtCsd ", searchDepth=30)
    if not img_click.Exists():
        img_click = auto.ButtonControl(ClassName="aoRNLd kn2E5e NMjTrf ", searchDepth=30)
        if not img_click.Exists():
            raise Exception("The image click not exists")
    img_click.Click()

def check_back_button_exists():
    back_btn = auto.ButtonControl(Name="Back", ClassName="iPpe6d", searchDepth=30)
    if not back_btn.Exists():
        return
    back_btn.Click()

def close_edge_window():
    edge_wnd = auto.WindowControl(ClassName="Chrome_WidgetWin_1", searchDepth=2)
    edge_wnd.GetWindowPattern().Close()

def final_grab():
    # recursive method to handle failed case
    busStations = get_bus_stations()
    busStations = ["63301 - paya lebar meth girls' sc"] + busStations

    is_open = True
    failed_cases = []
    for idx, busStation in enumerate(busStations):
        print(f"Work on bus station #{idx +1}")
        try:
            if idx == 0 or is_open:
                open_edge()
                open_google_map()
                search_google_map_place(place=busStation)
                click_on_place_image()
                capture_images(busStation, 2)

                is_open = False
                continue

            next_bus_station_search(place=busStation)
            second_image_click()
            capture_images(busStation, 3)
            check_back_button_exists()

        except Exception as err:

            print(f"ERROR: skip the {busStation} and close the windows, error is {err}")
            close_edge_window()
            is_open = True
            failed_cases.append(busStation)

    print("FINAL IMPORTANT: TOTAL NUMBERS OF FAILED CASES IS: ", len(failed_cases),
          " and the list is \n", failed_cases)

# def official_grab():
#     busStations = get_bus_stations()

#     try:
#         final_grab(busStations)

if __name__ == "__main__":
    final_grab()

    # place = "63301 - paya lebar meth girls' sc"
    # # place1 = "66351 - s'goon stn exit e"
    # # place2 = "66099 - opp golden hill est"
    # # place3 = "54109 - bef ang mo kio ave 10"
    # # place4 = "54101 - aft ang mo kio ave 10"
    # # place5 = "66091 - golden hill est"
    # # place6 = "63289 - aljunied cc"
    # # place7 = "63309 - blk 126"
    # busStations = get_bus_stations()

    # for idx, busStation in enumerate(busStations):
    #     if idx == 0:
    #         open_edge()
    #         open_google_map()
    #         search_google_map_place(place=busStation)
    #         click_on_place_image()
    #         capture_images(busStation, 2)
    #         continue

    #     next_bus_station_search(place=busStation)
    #     second_image_click()
    #     capture_images(busStation, 3)
    #     check_back_button_exists()
    #     print(f"Total of {idx} bus station done")
    # # (663, 199), (1811 , 937)
